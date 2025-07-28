#define VELOCIDAD 14
#define DIRPIN_1 12
#define DIRPIN_2 13

#define LEDROJO 15
#define LEDVERDE 4
#define LEDAZUL 0

#define PARO 0
#define DERECHA 1
#define IZQUIERDA 2

#define POT 33  // Pin donde está conectado el potenciómetro



void setup() {
  Serial.begin(115200);

  pinMode(VELOCIDAD, OUTPUT);
  pinMode(DIRPIN_1, OUTPUT);
  pinMode(DIRPIN_2, OUTPUT);

  pinMode(LEDROJO, OUTPUT);
  pinMode(LEDVERDE, OUTPUT);
  pinMode(LEDAZUL, OUTPUT);

  pinMode(POT, INPUT);
}

void loop() {
 
  cambioEstado(DERECHA);
  delay(5000);

  cambioEstado(PARO);
  delay(2000);

  cambioEstado(IZQUIERDA);
  delay(5000);

  cambioEstado(PARO);
  delay(2000);
}

void cambioEstado(int estadoNuevo) {

  switch (estadoNuevo) {
    case PARO:
      Serial.println("Motor parado.");
      analogWrite(VELOCIDAD, 0);
      digitalWrite(LEDROJO, HIGH);
      digitalWrite(LEDAZUL, LOW);
      digitalWrite(LEDVERDE, LOW);
      break;
    case DERECHA:
      Serial.println("Girando en una direccion.");
      analogWrite(VELOCIDAD, leerPot());
      digitalWrite(DIRPIN_1, LOW);
      digitalWrite(DIRPIN_2, HIGH);
      digitalWrite(LEDROJO, LOW);
      digitalWrite(LEDVERDE, HIGH);
      digitalWrite(LEDAZUL, LOW);
      break;
    case IZQUIERDA:
      Serial.println("Girando en otra direccion.");
      analogWrite(VELOCIDAD, leerPot());
      digitalWrite(DIRPIN_1, HIGH);
      digitalWrite(DIRPIN_2, LOW);
      digitalWrite(LEDROJO, LOW);
      digitalWrite(LEDVERDE, LOW);
      digitalWrite(LEDAZUL, HIGH);
      break;
    default:
      break;
  }
}

int leerPot(){
  int valorPot= 0;
  int valorVel = 0;

  valorPot = analogRead(POT);
  valorVel = map(valorPot,0,4096,80,255);

  Serial.println("Velocidad: "+String(valorVel));

  return valorVel;
}