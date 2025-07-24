#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Pines y configuración
#define SDA 13
#define SCL 14
#define ADDR 0x27  // Dirección I2C de la pantalla
#define DHTPIN 15   // Pin del DHT22
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(ADDR, 16, 2);

void setup() {
  Serial.begin(115200);

  Wire.begin(SDA, SCL);
  lcd.init();
  lcd.backlight();
  lcd.clear();

  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  lcd.clear();

  
    // Línea 1: Temperatura
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(t, 1); // Un decimal
    lcd.write(byte(223)); // Símbolo de grados °
    lcd.print("C");

    // Línea 2: Humedad
    lcd.setCursor(0, 1);
    lcd.print("Hum: ");
    lcd.print(h, 0); // Sin decimales
    lcd.print("%");

  delay(2000);  // Espera entre lecturas
}
