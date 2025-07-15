#define PULSADOR 13
#define LED 4
#define ZUMBADOR 15

int valorBoton = LOW;
int estado = LOW;

void setup() {
  pinMode(PULSADOR, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(ZUMBADOR, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  valorBoton =  digitalRead(PULSADOR);

  if(valorBoton == LOW) {
    digitalWrite(LED, HIGH);
    digitalWrite(ZUMBADOR,HIGH);
  }else{
    digitalWrite(LED, LOW);
    digitalWrite(ZUMBADOR,LOW);
  }

  // if(valorBoton == LOW){
  //  estado = !estado;
  //  digitalWrite(LED, estado);
  // }

  delay(100);
}
