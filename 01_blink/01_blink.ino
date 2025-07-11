#define PIN_ROJO 12
#define PIN_LED 2 //Definicion del pin del led del microcontrolador de la placa esp32
int contador = 0; // Eso inicializa el contador al principio y si esta en el loop se inicializa todo el rato 
void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_ROJO, OUTPUT);
  Serial.begin(115200); //Velocidad de la comunicación
  Serial.println("Serial encendido"); // Es posible que no salga en el serial porque tarda en reaccionar cuando se inicialize
}
void loop() {
  digitalWrite(PIN_LED, HIGH);
  digitalWrite(PIN_ROJO, LOW);
  /*
  Las tres siguientes son similares: 
    - contador = contador +1;
    - contador += 1;
    - contador ++;
  */
  Serial.println(contador);
  Serial.println("Se ha encendido");
  delay(500);
  contador ++;
  digitalWrite(PIN_LED, LOW);
  digitalWrite(PIN_ROJO, HIGH);
  Serial.println("Se ha apagado");
  delay(500);
}
