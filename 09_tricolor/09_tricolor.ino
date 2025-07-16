#define ROJO 15
#define AZUL 12
#define VERDE 13

void setup() {
  // put your setup code here, to run once:

  pinMode(ROJO, OUTPUT);
  pinMode(AZUL, OUTPUT);
  pinMode(VERDE, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
/*
  //Rojo
  digitalWrite(ROJO, LOW);  //En el led RGB Low significa encendido y HIGH es apagado
  digitalWrite(VERDE, HIGH);
  digitalWrite(AZUL, HIGH);

  delay(500);
  //Rojo
  digitalWrite(ROJO, LOW);  //En el led RGB Low significa encendido y HIGH es apagado
  digitalWrite(VERDE, LOW);
  digitalWrite(AZUL, HIGH);

  delay(500);

    digitalWrite(ROJO, LOW);  //En el led RGB Low significa encendido y HIGH es apagado
  digitalWrite(VERDE, HIGH);
  digitalWrite(AZUL, LOW);

  delay(500);
  //Rojo
  digitalWrite(ROJO, HIGH);  //En el led RGB Low significa encendido y HIGH es apagado
  digitalWrite(VERDE, LOW);
  digitalWrite(AZUL, HIGH);

  delay(500);
   //Rojo
  digitalWrite(ROJO, HIGH);  //En el led RGB Low significa encendido y HIGH es apagado
  digitalWrite(VERDE, LOW);
  digitalWrite(AZUL, LOW);

  delay(500);

   digitalWrite(ROJO, HIGH);  //En el led RGB Low significa encendido y HIGH es apagado
  digitalWrite(VERDE, HIGH);
  digitalWrite(AZUL, LOW);

  delay(500);

 digitalWrite(ROJO, LOW);  //En el led RGB Low significa encendido y HIGH es apagado
  digitalWrite(VERDE, LOW);
  digitalWrite(AZUL, LOW);

  delay(500);

    digitalWrite(ROJO, LOW);  //En el led RGB Low significa encendido y HIGH es apagado
  digitalWrite(VERDE, LOW);
  digitalWrite(AZUL, HIGH);

  delay(500);
  */

  
  int r = 0;
  int g = 0;
  int b = 0;

  for(;;){
    r = random(0,255);
    g = random(0,255);
    b = random(0,255);

    analogWrite(ROJO,r);
    analogWrite(VERDE,g);
    analogWrite(VERDE,b);

    delay(1000);
  }
}
