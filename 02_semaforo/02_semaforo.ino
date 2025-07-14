#define PIN_ROJO 12
#define PIN_VERDE 13
#define PIN_AZUL 14

void setup() {
  Serial.begin(115200);
  pinMode(PIN_ROJO, OUTPUT);
  pinMode(PIN_AZUL, OUTPUT);
  pinMode(PIN_VERDE, OUTPUT);
}
void loop() {
  //Led rojo encendido
  digitalWrite(PIN_ROJO, HIGH);
  digitalWrite(PIN_AZUL, LOW);
  digitalWrite(PIN_VERDE,LOW);
  Serial.print("Led rojo encendido. \n");//Otra manera de poner el Serial.println
  delay(1000);
  //Led azul encendido
   digitalWrite(PIN_ROJO, LOW);
   //Parpadeo del led azul como el color amarillo de los semaforos normales
  digitalWrite(PIN_AZUL, HIGH);
  delay(500);
  digitalWrite(PIN_AZUL,LOW);
  delay(500);
  digitalWrite(PIN_AZUL, HIGH);
  delay(500);
  digitalWrite(PIN_VERDE,LOW); 
  Serial.print("Led azul encendido. \n");//Otra manera de poner el Serial.println

  delay(500);
  //Led verde encendido
   digitalWrite(PIN_ROJO, LOW);
  digitalWrite(PIN_AZUL, LOW);
  digitalWrite(PIN_VERDE,HIGH);
  Serial.print("Led verde encendido. \n"); //Otra manera de poner el Serial.println
  delay(1000);
}
