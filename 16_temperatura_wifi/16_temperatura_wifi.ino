#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define DHTTYPE DHT11
#define DHTPIN 13

float temp = 0.0;
float hum = 0.0;

DHT dht(DHTPIN, DHTTYPE);

//conexion a internet

WiFiClient clienteWifi;
HTTPClient http;

char* servidor = "http://192.168.0.31:5000/datos";

//WIFI
char* ssid = "Aula 1";
char* pass = "Horus.2025";


void setup() {
  Serial.begin(115200);

  dht.begin();

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Conectado a la IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  hum = dht.readHumidity();
  temp = dht.readTemperature();

  postData(temp, hum, "Natalia Local");
  // Serial.print("La temperatura es :");
  // Serial.println(temp);

  // Serial.print("La humedad es :");
  // Serial.println(hum);
  delay(5000);
}

void postData(float t, float h, String per) {
  String parametros = "temp=" + String(t) + "&hum=" + String(h) + "&persona=" + per;
  int httpCode;
  String payload;
  if (WiFi.status() == WL_CONNECTED) {
    http.begin(clienteWifi, servidor);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    httpCode = http.POST(parametros);
    payload = http.getString();

    Serial.print("HTTP Code: ");
    Serial.println(httpCode);
    Serial.print("Mensaje: ");
    Serial.println(payload);
    
  }
}