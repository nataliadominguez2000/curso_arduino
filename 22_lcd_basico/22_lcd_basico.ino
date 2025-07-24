#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define SDA 13
#define SCL 14
#define ADDR 0x27

LiquidCrystal_I2C lcd(ADDR,16,2);

void setup() {
  // put your setup code here, to run once:
  Wire.begin(SDA,SCL);
  lcd.init();
  lcd.noBacklight();
  delay(1000);
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("hello, world!");
   lcd.setCursor(0,1);
  lcd.print("Bienvenidos ...");
}

void loop() {
  // put your main code here, to run repeatedly:

  // lcd.display();
  // delay(500);
  // lcd.noDisplay();
  // delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp: 28.50");
  lcd.print(char(223));
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Hum: 40%");
  delay(5000);
}
