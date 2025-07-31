#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

char* ssid = "Aula 1";
char* pwd = "Horus.2025";

//MQTT
WiFiClient espClient;
PubSubClient client(espClient);

char* mqtt_server = "192.168.0.25";
int mqtt_port = 1883;

char* mqtt_topic_sub = "curso_arduino/#";

char* mqtt_topic_pub = "curso_arduino/natalia/temperatura";
char* mqtt_client_id = "ESP_Natalia";

static unsigned long lastMsg = 0;
unsigned long now = 0;

//DHT sensor
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

float temp = 0.0;
float hum = 0.0;

char tempStr[8];  //Será de 8 bytes
char humStr[8];   //Será de 8 bytes



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n");
  Serial.println(WiFi.localIP());

  //MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  dht.begin();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  temp = dht.readTemperature();
  hum = dht.readHumidity();

  dtostrf(temp, 1, 2, tempStr);  //transforma un float con un array de char
  dtostrf(hum, 1, 2, humStr);

  client.publish("curso_arduino/natalia/temperatura", tempStr);
  client.publish("curso_arduino/natalia/humedad", humStr);

  Serial.println("Temp: "+String(temp));
  Serial.println("Hum: "+String(hum));
  delay(5000);
}

//Mensaje recibido en [curso_arduino/natalia]:hola mundo
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje recibido en [");
  Serial.print(topic);
  Serial.print("]:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Reconectando...");
    if (client.connect(mqtt_client_id)) {
      Serial.println("Conectado a MQTT");
      client.subscribe(mqtt_topic_sub);
    } else {
      Serial.println(" Fallo en la conexión");
      Serial.println("Error: " + client.state());
      delay(5000);
    }
  }
}
