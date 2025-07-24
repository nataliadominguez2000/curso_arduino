#include <Wire.h>                  // Librería para comunicación I2C
#include <LiquidCrystal_I2C.h>     // Librería para manejar pantallas LCD con I2C
#include <WiFi.h>                  // Librería para conectarse a redes WiFi
#include "time.h"                  // Librería para obtener la hora desde internet (NTP)

// CONFIGURACIÓN DEL LCD
#define SDA 13                     // Pin SDA (datos) del I2C
#define SCL 14                     // Pin SCL (reloj) del I2C
#define ADDR 0x27                  // Dirección del LCD I2C
LiquidCrystal_I2C lcd(ADDR, 16, 2);  // Crear objeto LCD de 16x2

// CONFIGURACIÓN DE WIFI
const char* ssid = "Aula 1";       // Nombre de la red WiFi
const char* password = "Horus.2025"; // Contraseña de la red WiFi

// CONFIGURACIÓN DE NTP (servidor de hora)
const char* ntpServer = "pool.ntp.org"; // Servidor que da la hora por internet
const long  gmtOffset_sec = 0;          // Diferencia horaria con GMT (en segundos)
const int   daylightOffset_sec = 7200;  // Horario de verano (+2 horas)

void setup() {
  Wire.begin(SDA, SCL);           // Iniciar comunicación I2C con los pines indicados
  lcd.init();                     // Iniciar pantalla LCD
  lcd.backlight();                // Encender luz de fondo del LCD

  lcd.setCursor(0, 0);            // Mover cursor a la primera fila
  lcd.print("Conectando WiFi");  // Mostrar mensaje

  WiFi.begin(ssid, password);    // Intentar conectarse al WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);                   // Esperar medio segundo
    lcd.print(".");               // Mostrar puntos mientras se conecta
  }

  lcd.clear();                    // Limpiar pantalla
  lcd.setCursor(0, 0);
  lcd.print("WiFi conectada!");  // Mensaje cuando se conecta correctamente

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer); // Sincronizar hora con el servidor NTP

  delay(1000); // Esperar un segundo
}

void loop() {
  lcd.clear();                    // Limpiar pantalla en cada vuelta

  struct tm timeinfo;             // Estructura para guardar la hora actual
  if (!getLocalTime(&timeinfo)) { // Si no se puede obtener la hora...
    lcd.setCursor(0, 0);
    lcd.print("Error NTP");       // Mostrar error
    delay(1000);                  // Esperar un segundo
    return;                       // Salir del loop y volver a intentarlo
  }

  // Mostrar la fecha (formato: YYYY/MM/DD)
  lcd.setCursor(0, 0);
  char fecha[17];                 // Arreglo para guardar la fecha
  strftime(fecha, sizeof(fecha), "%Y/%m/%d", &timeinfo); // Formatear fecha
  lcd.print(fecha);              // Mostrar fecha en la primera línea

  // Mostrar la hora (formato: HH:MM)
  lcd.setCursor(0, 1);           // Segunda línea del LCD
  char hora[17];                 // Arreglo para guardar la hora
  strftime(hora, sizeof(hora), "%H:%M", &timeinfo); // Formatear hora
  lcd.print(hora);               // Mostrar hora

  delay(1000);                   // Esperar un segundo antes de actualizar
}
