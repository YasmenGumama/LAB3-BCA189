#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

// Initialize the DS1307 RTC and LCD objects
RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
  Serial.begin(115200);
  Wire.begin(); 

  // Initialize LCD
  lcd.begin();      
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("System Booting..");

  // Initialize RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    lcd.clear();
    lcd.print("RTC Error!");
    while (1) delay(10); // Halt execution
  }

  // If the RTC is not running, set it to the time the sketch was compiled
  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running, setting time...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  
  delay(2000);
  lcd.clear();
}

void loop() {
  DateTime now = rtc.now();

  // --- 1. Print Data to Serial Monitor ---
  Serial.print("Date: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  
  Serial.print(" | Time: ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);

  // --- 2. Print Data to LCD Display ---
  // Row 0: Date
  lcd.setCursor(0, 0);
  lcd.print("Date: ");
  lcd.print(now.year(), DEC);
  lcd.print('/');
  if(now.month() < 10) lcd.print('0');
  lcd.print(now.month(), DEC);
  lcd.print('/');
  if(now.day() < 10) lcd.print('0');
  lcd.print(now.day(), DEC);

  // Row 1: Time
  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  if(now.hour() < 10) lcd.print('0');
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  if(now.minute() < 10) lcd.print('0');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  if(now.second() < 10) lcd.print('0');
  lcd.print(now.second(), DEC);

  delay(1000);
}