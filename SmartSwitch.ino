#include <IRremote.hpp>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

// ------------------- Pins -------------------
#define IR_RECEIVE_PIN 2
#define SERVO1_PIN 5
#define SERVO2_PIN 6
#define RST_PIN 9
#define SS_PIN 10
#define BUZZER_PIN 3

// ------------------- Servo Angles -------------------
#define SERVO1_ON 10
#define SERVO1_OFF 100
#define SERVO2_ON 100
#define SERVO2_OFF 10

// ------------------- Objects -------------------
Servo servo1;
Servo servo2;
MFRC522 mfrc522(SS_PIN, RST_PIN);

// ------------------- Variables -------------------
bool servo1AtStart = true;
bool servo2AtStart = true;
bool remoteEnabled = false;

// Correct card UID (change this to your card UID)
byte correctUID[4] = {0xF2, 0x32, 0x86, 0x04};

void setup() {
  Serial.begin(9600);

  // IR Receiver
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  // Servos
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo1.write(SERVO1_OFF);
  servo2.write(SERVO2_OFF);

  // RFID
  SPI.begin();
  mfrc522.PCD_Init();

  // Buzzer
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println("Scan your RFID card to enable remote control...");
}

void loop() {
  // -------- RFID Authentication --------
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    if (checkUID()) {
      Serial.println("✅ Correct card scanned! Remote enabled.");
      remoteEnabled = true;
      buzzSuccess();
      resetServos();
    } else {
      Serial.println("❌ Wrong card. Remote locked.");
      remoteEnabled = false;
      buzzFail();
    }
    mfrc522.PICC_HaltA();
  }

  // -------- IR Remote Handling --------
  if (remoteEnabled && IrReceiver.decode()) {
    uint8_t command = IrReceiver.decodedIRData.command;
    String protocol = IrReceiver.getProtocolString();

    Serial.print("Received code: 0x");
    Serial.println(command, HEX);

    if (protocol == "NEC") {
      // Servo 1
      if (command == 0xC) {
        toggleServo1();
      }
      // Servo 2
      else if (command == 0x18) {
        toggleServo2();
      }
    }
    IrReceiver.resume();
  }
}

// ------------------- Helper Functions -------------------
bool checkUID() {
  for (byte i = 0; i < 4; i++) {
    if (mfrc522.uid.uidByte[i] != correctUID[i]) {
      return false;
    }
  }
  return true;
}

void buzzSuccess() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);
}

void buzzFail() {
  for (int i = 0; i < 2; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(50);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
  }
}

void resetServos() {
  servo1.write(SERVO1_OFF);
  servo2.write(SERVO2_OFF);
  servo1AtStart = true;
  servo2AtStart = true;
}

void toggleServo1() {
  if (servo1AtStart) {
    servo1.write(SERVO1_ON);
  } else {
    servo1.write(SERVO1_OFF);
  }
  servo1AtStart = !servo1AtStart;
  delay(300);
}

void toggleServo2() {
  if (servo2AtStart) {
    servo2.write(SERVO2_ON);
  } else {
    servo2.write(SERVO2_OFF);
  }
  servo2AtStart = !servo2AtStart;
  delay(300);
}
