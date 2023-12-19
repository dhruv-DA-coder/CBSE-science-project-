#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27, 16 column and 2 rows

const int mq2Pin = A0;  // Analog pin for MQ2 sensor
const int mq5Pin = A1;  // Analog pin for MQ5 sensor
const int buzzerPin = 8;  // Digital pin for the buzzer

// Define threshold values for smoke detection
const int mq2Threshold = 400;  // Adjust this based on sensor calibration
const int mq5Threshold = 300;  // Adjust this based on sensor calibration

void setup() {
  lcd.begin(16, 2);  // Initialize the LCD
  lcd.backlight();

  pinMode(buzzerPin, OUTPUT);  // Set buzzer pin as output
}

void loop() {
  // Read analog values from MQ2 and MQ5 sensors
  int mq2Value = analogRead(mq2Pin);
  int mq5Value = analogRead(mq5Pin);

  // Display sensor readings on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MQ2: ");
  lcd.print(mq2Value);
  lcd.setCursor(0, 1);
  lcd.print("MQ5: ");
  lcd.print(mq5Value);

  // Check if smoke is detected by MQ2 sensor
  if (mq2Value > mq2Threshold) {
    lcd.clear();
    lcd.print("Smoke detected!");
    activateBuzzer();
    delay(5000);  // Display the warning for 5 seconds
  }

  // Check if smoke is detected by MQ5 sensor
  if (mq5Value > mq5Threshold) {
    lcd.clear();
    lcd.print("Smoke detected!");
    activateBuzzer();
    delay(5000);  // Display the warning for 5 seconds
  }
}

void activateBuzzer() {
  digitalWrite(buzzerPin, HIGH);  // Turn on the buzzer
  delay(1000);  // Beep for 1 second
  digitalWrite(buzzerPin, LOW);   // Turn off the buzzer
}
