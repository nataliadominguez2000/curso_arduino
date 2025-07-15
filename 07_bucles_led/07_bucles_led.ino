#define LED 2
#define ZUMBADOR 15

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(ZUMBADOR,OUTPUT);
}

int duracion = 20;
void loop() {
  // put your main code here, to run repeatedly:

for(int veces = 0; veces < 10; veces ++){
  
  digitalWrite(LED,HIGH);
  digitalWrite(ZUMBADOR,HIGH);
  delay(duracion);
  duracion = duracion + veces * 10;
  digitalWrite(LED,LOW);
  digitalWrite(ZUMBADOR,LOW);
  delay(duracion);
  Serial.println(duracion); //Por si queremos saber cuando es el tiempo de la duracion con el zumbador 
}

}
