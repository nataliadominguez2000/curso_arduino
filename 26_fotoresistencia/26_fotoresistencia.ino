#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define SDA 13
#define SCL 14
#define ADDR 0X27
LiquidCrystal_I2C lcd(ADDR,16,2);

#define FOTO_PIN 4     // Pin donde está conectada la fotorresistencia (LDR)
#define LED 2          // Pin del LED (integrado en la placa ESP32)
#define UMBRAL 2000

int valorLuz = 0;       // Variable para guardar la lectura del sensor
int valorLed = 0;       // Valor que se enviará al LED (PWM)

void setup() {
  pinMode(FOTO_PIN, INPUT);   // Configurar el pin del LDR como entrada
  pinMode(LED, OUTPUT);       // Configurar el LED como salida
  Serial.begin(115200);         // Iniciar monitor serie para depuración

 Wire.begin(SDA,SCL);
  lcd.init();
  lcd.noBacklight();
  delay(1000);
  lcd.backlight();
}

void loop() {
  // Leer valor de la fotorresistencia (0 a 4095 en ESP32)
  lcd.clear();
  valorLuz = analogRead(FOTO_PIN);

  // Invertir valor para que cuando haya más oscuridad, el LED brille más
  valorLed = map(valorLuz, 0, 4095,255,0);

  // Escribir el valor PWM al LED (ajusta su brillo)
  // analogWrite(LED, valorLed); // En ESP32 se puede usar ledcWrite si no funciona
if(valorLuz > UMBRAL){
  digitalWrite(LED,HIGH);
}else {
  digitalWrite(LED,LOW);
}
  // Mostrar valores por la pantalla LCD
  lcd.setCursor(0,0);
  lcd.print("Luz: ");
  lcd.print(valorLuz);
  lcd.setCursor(0, 1);
  lcd.print(" LED: ");
  lcd.print(valorLed);



  delay(500); // Pequeña pausa
}

