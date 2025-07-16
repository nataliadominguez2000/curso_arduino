#include <DHT.h>

#define DHTPIN 13
#define DHTTYPE DHT11
#define PINLED 15

//Tipo para el metodo de DHT
DHT dht(DHTPIN, DHTTYPE);

float temp = 0.0;
float hum = 0.0;

void setup() {

  Serial.begin(115200);
  dht.begin();
  pinMode(PINLED,OUTPUT);
  // put your setup code here, to run once:
}

void loop() {
    digitalWrite(PINLED,HIGH);
  temp = dht.readTemperature();
  hum = dht.readHumidity();

  Serial.print("La temperatura es :");
  Serial.println(temp);

  Serial.print("La humedad es :");
  Serial.println(hum);
  digitalWrite(PINLED,LOW);

  delay(2000);
}
