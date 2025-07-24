#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <WiFi.h>

#define SDA 13
#define SCL 14
#define ADDR 0x27

char* ssid = "Aula 1";
char* pwd = "Horus.2025";

LiquidCrystal_I2C lcd(ADDR,16,2);

void setup() {
  // put your setup code here, to run once:
  Wire.begin(SDA,SCL);
 lcd.init();
 lcd.backlight();
 lcd.setCursor(0, 0);
 lcd.print("Conectando ...");

 WiFi.begin(ssid,pwd);
 int attempts = 0;
 while (WiFi.status() != WL_CONNECTED && attempts < 20) {
 delay(500);
 lcd.setCursor(0,1);
 lcd.print(".");
 attempts++;
 }
 lcd.clear();
 if (WiFi.status() == WL_CONNECTED) {
    lcd.setCursor(0, 0);
    lcd.print("WiFi conectado!");

    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("IP local:");
    lcd.setCursor(0, 1);
    lcd.print(WiFi.localIP());
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Error WiFi");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  // lcd.display();
  // delay(500);
  // lcd.noDisplay();
  // delay(500);
 
}
