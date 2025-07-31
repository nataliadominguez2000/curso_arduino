
//Definicion de los LED
#define ROJO 12
#define AZUL 13

TaskHandle_t Tarea0; //Tarea0 parpadeo LED 300 milisegundos
TaskHandle_t Tarea1; //Tarea1 parpadeo LED 1 Segundo

void loop0(void *parameter);
void loop1(void *parameter);

void setup() {
  // put your setup code here, to run once:
  xTaskCreatePinnedToCore(loop0, "Tarea_0", 1000, NULL, 1, &Tarea0, 0);
  xTaskCreatePinnedToCore(loop1, "Tarea_1", 1000, NULL, 1, &Tarea1, 1);
  pinMode(ROJO, OUTPUT);
  pinMode(AZUL, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void loop0(void *parameter) {
  //Tarea0 parpadeo LED 300 milisegundos
  while (true) {
    digitalWrite(AZUL, HIGH);
    delay(300);
    digitalWrite(AZUL, LOW);
    delay(300);
  }
}
void loop1(void *parameter) {
  // Tarea1 parpadeo LED 1 Segundo
  while (true) {
    digitalWrite(ROJO, HIGH);
    delay(1000);
    digitalWrite(ROJO, LOW);
    delay(1000);
  }
}