#include <DHT.h>

// Pin del DHT22 y del ventilador
#define DHTPIN 4
#define DHTTYPE DHT11
#define FAN_PIN 12
#define OK_LED_PIN 13 //LED que se enciende cunado NO se activa el ventilador

// Objeto DHT
DHT dht(DHTPIN, DHTTYPE);

// Variables compartidas
float temperature = 0.0;

// Mutex para proteger acceso a la variable compartida
SemaphoreHandle_t tempMutex;

// Tarea 1: Lee el sensor de temperatura
void readTemperatureTask(void *pvParameters) {
  while (true) {
    float temp = dht.readTemperature();
    if (!isnan(temp)) {
      xSemaphoreTake(tempMutex, portMAX_DELAY);
      temperature = temp;
      xSemaphoreGive(tempMutex);
    }
    Serial.println(temp);
    vTaskDelay(pdMS_TO_TICKS(2000));  // cada 2 segundos
  }
}

// Tarea 2: Controla el ventilador
void fanControlTask(void *pvParameters) {
  const float threshold = 26.0;  // temperatura umbral

  while (true) {
    xSemaphoreTake(tempMutex, portMAX_DELAY);
    float currentTemp = temperature;
    xSemaphoreGive(tempMutex);

    if (currentTemp >= threshold) {
      digitalWrite(FAN_PIN, HIGH);  // encender ventilador
      digitalWrite(OK_LED_PIN, LOW);
    } else {
      digitalWrite(FAN_PIN, LOW);   // apagar ventilador
      digitalWrite(OK_LED_PIN, HIGH);
    }

    vTaskDelay(pdMS_TO_TICKS(1000));  // revisar cada 1 segundo
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);
  pinMode(OK_LED_PIN, OUTPUT);
  digitalWrite(OK_LED_PIN, LOW);

  tempMutex = xSemaphoreCreateMutex();

  // Crear tareas
  xTaskCreatePinnedToCore(readTemperatureTask, "ReadTemp", 2048, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(fanControlTask, "FanControl", 2048, NULL, 1, NULL, 1);
}

void loop() {
  // No se usa en FreeRTOS
}