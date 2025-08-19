# 🔌 Smart Switch (Touchless IoT Prototype)

A **smart home project** developed at English For IT Camp 🏕️.  
It allows controlling a traditional wall switch **without touching mains wiring** by using **RFID authentication + IR remote + servos**.

---

## 🚀 Features
- **Secure access**: IR remote only works after scanning the correct RFID card.
- **Dual servo motors**: Physically toggle switches without rewiring mains electricity.
- **Visual + audio feedback**: Buzzer signals successful or failed authentication.
- **Expandable**: Can support multiple RFID cards or be upgraded to WiFi/IoT.

---

## 🛠️ Hardware Used
- Arduino Uno  
- 2x Servo Motors  
- IR Remote + Receiver  
- RFID Module (MFRC522)  
- Buzzer  
- Jumper wires, breadboard, and power source  

---

## ⚡ Wiring Diagram
| Component     | Pin on Arduino |
|---------------|----------------|
| IR Receiver   | D2             |
| Servo 1       | D5             |
| Servo 2       | D6             |
| RFID RST      | D9             |
| RFID SDA (SS) | D10            |
| Buzzer        | D3             |

---

## 💻 Code
See [SmartSwitch.ino](SmartSwitch.ino) for full implementation.

---

## ▶️ Usage
1. Upload the code to Arduino Uno.  
2. Power up the circuit.  
3. Scan the **authorized RFID card** → IR remote gets unlocked.  
4. Use IR remote buttons:
   - Button `0xC` → Toggles Servo 1  
   - Button `0x18` → Toggles Servo 2  

---

## 📸 Demo
![telegram-cloud-photo-size-2-5255783370703643420-y](https://github.com/user-attachments/assets/96abccb1-e07e-486b-bcad-4f336ce1d92f)


---

## 👨‍💻 Authors
Team project by **SAM production** at **English For IT Camp**.  
Recognized as one of the **Top 3 Projects** 🎉.

---

## 📜 License
This project is released under the [MIT License](LICENSE).  
