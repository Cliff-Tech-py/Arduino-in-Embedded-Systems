/*
================================================================================
Arduino Keypad Door Lock System with LCD, Servo, Buzzer & LEDs
================================================================================
Author: Wycliff Muriuki
Date: 2025/08/10
License: MIT License

Description:
------------
This project implements a PIN-based security system using an Arduino Uno, a 4x4 
keypad, an I2C 16x2 LCD, a servo motor, a buzzer, and two LEDs (red & green).

Features:
---------
- LCD prompts user to "Enter The Pin"
- 4x4 Keypad for PIN entry
- Correct PIN:
    * Green LED turns on
    * Servo rotates 90° (door unlock)
    * "Welcome" displayed on LCD
- Wrong PIN:
    * Red LED blinks twice
    * Buzzer beeps twice
    * "Wrong Pin, Try Again" displayed
- Press '*' to clear input
- Press '#' to submit PIN
- Easily customizable PIN by changing `correctPIN` variable

Required Components:
--------------------
1. Arduino Uno
2. 4x4 Matrix Keypad
3. 16x2 LCD with I2C interface
4. Servo motor
5. Active buzzer
6. Red LED
7. Green LED
8. 220Ω resistors (for LEDs)
9. Jumper wires & breadboard

Wiring Summary:
---------------
LCD (I2C) → SDA → A4, SCL → A5  
Keypad R1–R4 → D2, D3, D4, D5  
Keypad C1–C4 → D6, D7, D8, D9  
Servo signal → D10  
Buzzer → D11  
Red LED → D12 (with resistor)  
Green LED → D13 (with resistor)  

Library Dependencies:
---------------------
- LiquidCrystal_I2C
- Wire
- Keypad
- Servo

Simulation:
-----------
This project can be simulated using Tinkercad Circuits by wiring the components 
as described and uploading this code.

Customization:
--------------
- Change the correct PIN in `String correctPIN = "1234";`
- Adjust servo angles in `myServo.write()` calls for your lock mechanism
- Modify buzzer/LED patterns for wrong attempts

================================================================================
*/

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>
#include <Servo.h>

// ===== LCD =====
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change 0x27 if LCD address differs

// ===== Keypad Setup =====
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5}; // R1-R4
byte colPins[COLS] = {6, 7, 8, 9}; // C1-C4
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ===== Servo =====
Servo myServo;
int servoPin = 10;

// ===== LEDs & Buzzer =====
int buzzerPin = 11;
int redLED = 12;
int greenLED = 13;

// ===== Security =====
String correctPIN = "1234"; // Change your PIN here
String enteredPIN = "";

void setup() {
  lcd.init();
  lcd.backlight();

  myServo.attach(servoPin);
  delay(200);         // give servo time to stabilize
  myServo.write(0);   // start at 0 degrees
  delay(200);         // small pause so it doesn't jerk

  pinMode(buzzerPin, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter The Pin");
}


void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') { 
      checkPIN();
    } 
    else if (key == '*') { 
      enteredPIN = "";
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enter The Pin");
    }
    else {
      enteredPIN += key;
      lcd.setCursor(0, 1);
      lcd.print(enteredPIN); // Shows digits directly
    }
  }
}

void checkPIN() {
  if (enteredPIN == correctPIN) {
    lcd.clear();
    lcd.print("Welcome");
    digitalWrite(greenLED, HIGH);
    myServo.write(90); // rotate servo 90 degrees
    delay(3000); // wait 3 seconds
    myServo.write(0); // return to 0
    digitalWrite(greenLED, LOW);
  } else {
    lcd.clear();
    lcd.print("Wrong Pin");
    lcd.setCursor(0, 1);
    lcd.print("Try Again");

    // Beep buzzer & red LED twice
    for (int i = 0; i < 2; i++) {
      digitalWrite(buzzerPin, HIGH);
      digitalWrite(redLED, HIGH);
      delay(200);
      digitalWrite(buzzerPin, LOW);
      digitalWrite(redLED, LOW);
      delay(200);
    }
  }
  enteredPIN = "";
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter The Pin");
}
