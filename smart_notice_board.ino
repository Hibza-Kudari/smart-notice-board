#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// Create LiquidCrystal Object for LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

// Define SoftwareSerial for Bluetooth (RX, TX)
SoftwareSerial mySerial(2, 3);  // Connect Bluetooth TX to Pin 2, RX to Pin 3

String val = "";      // To store incoming Bluetooth data
String oldval = "";   // To compare previous message
int i = 0;            // Cursor position on LCD

void setup() {
  lcd.begin(16, 2);        // Initialize 16x2 LCD
  mySerial.begin(9600);    // Start Bluetooth communication
  Serial.begin(9600);      // Start Serial monitor for debugging

  lcd.setCursor(0, 0);
  lcd.print("BYTE BUILDERS");
  lcd.setCursor(0, 1);
  lcd.print("Waiting for input...");
  delay(3000);  // 3-second delay
  lcd.clear();
  lcd.print("Ready!");
  delay(1000);
  lcd.clear();
}

void loop() {
  // Check for new Bluetooth input
  if (mySerial.available()) {
    char receivedChar = mySerial.read();
    val += receivedChar;

    // Check for newline character or end of input
    if (receivedChar == '\n' || receivedChar == '\r') {
      val.trim();  // Clean up the input
      Serial.println("Received: " + val);

      if (val != oldval) {
        oldval = val;
        i = 0;             // Reset cursor
        lcd.clear();       // Clear only on new message
      }

      lcd.setCursor(i, 0);
      lcd.print(val);      // Display on LCD
      val = "";            // Clear value for next input
      delay(100);          // Short delay
    }
  }

  // Scroll the display or wrap text
  i++;
  if (i >= 16) {
    i = 0;
  }
}
