#include <Keypad.h>

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {7, 6, 5, 4}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {3, 2, 9, 8}; // Connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const String password = "1234"; // Change this to the desired password
String input = "";

void setup() {
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  // Ensure motor is stopped initially
  digitalWrite(12, LOW); 
  digitalWrite(11, LOW); 
  Serial.println("System initialized. Waiting for input...");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.print("Key pressed: ");
    Serial.println(key); // For debugging

    if (key == '#') {
      input = ""; // Clear input if '#' is pressed
      Serial.println("Input cleared");
    } else if (key == '*') {
      Serial.print("Entered password: ");
      Serial.println(input);
      if (input == password) {
        Serial.println("Password correct! Unlocking...");
        digitalWrite(12, HIGH); // Set motor direction
        digitalWrite(11, LOW); // Start motor
        delay(5000); // Keep the lock open for 5 seconds
        digitalWrite(11, HIGH); // Stop motor
        digitalWrite(12, LOW); // Reset motor direction
        Serial.println("Lock closed");
      } else {
        Serial.println("Password incorrect!");
      }
      input = ""; // Clear input after checking
    } else {
      input += key; // Append the key pressed to the input
      Serial.print("Current input: ");
      Serial.println(input);
    }
  }
}
