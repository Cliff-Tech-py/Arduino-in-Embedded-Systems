# Arduino Keypad Door Lock System

## 📌 Overview
This project is a **PIN-based security system** built with an **Arduino Uno**, **4x4 Keypad**, **16x2 LCD (I2C)**, **Servo Motor**, **Buzzer**, and **LED indicators**.  
It simulates an electronic door lock that unlocks only when the correct PIN is entered.

---

## 🛠 Features
- Displays `"Enter The Pin"` prompt on LCD.
- Accepts PIN input from a 4x4 keypad.
- Correct PIN:
  - Rotates servo motor 90° (door unlock).
  - Turns on **green LED**.
  - Displays `"Welcome"` on LCD.
- Wrong PIN:
  - Buzzer beeps twice.
  - **Red LED** blinks twice.
  - Displays `"Wrong Pin Try Again"` on LCD.
- Press `*` to clear the entered PIN.
- Press `#` to submit the PIN.

---

## 📂 Components Required
| Component        | Quantity |
|------------------|----------|
| Arduino Uno      | 1        |
| 4x4 Keypad       | 1        |
| 16x2 LCD (I2C)   | 1        |
| Servo Motor      | 1        |
| Buzzer           | 1        |
| Red LED          | 1        |
| Green LED        | 1        |
| 220Ω Resistors   | 2        |
| Jumper Wires     | -        |
| Breadboard       | 1        |

---

## 🔌 Pin Connections
| Component  | Arduino Pin(s) |
|------------|----------------|
| LCD (I2C)  | SDA → A4, SCL → A5 |
| Keypad R1–R4 | 2, 3, 4, 5 |
| Keypad C1–C4 | 6, 7, 8, 9 |
| Servo      | 10 |
| Buzzer     | 11 |
| Red LED    | 12 |
| Green LED  | 13 |

---

## 💻 Libraries Used
Install these libraries in the Arduino IDE:
- `LiquidCrystal_I2C`
- `Wire`
- `Keypad`
- `Servo`

---

## 🚀 How It Works
1. On startup, the LCD prompts `"Enter The Pin"`.
2. User enters the PIN using the keypad.
3. Press `#` to submit:
   - If correct → Servo rotates 90°, green LED turns on, LCD shows `"Welcome"`.
   - If wrong → Buzzer beeps twice, red LED blinks, LCD shows `"Wrong Pin Try Again"`.
4. Press `*` to clear input and try again.

---

## 🖼 Simulation
You can simulate the circuit in **Tinkercad**:
- Add components as per the **Pin Connections** table.
- Upload the provided Arduino sketch.
- Open the Serial Monitor/LCD to test PIN entry.

---

## 📷 Future Improvements
- Add EEPROM storage to save PIN after power-off.
- Add multiple user PIN support.
- Integrate RFID for dual authentication.
- Control a real door lock mechanism instead of a servo.

---

## 📝 Author
Developed by Wycliff Muriuki  
Licensed under the MIT License.
