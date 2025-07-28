#include <Wire.h>
#include <LiquidCrystal_I2C.h> 

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

#define SDA 18
#define SCL 19
#define ADDR 0x27

LiquidCrystal_I2C lcd(ADDR,16,2);

void setup() {
  Serial.begin(115200);

  pinMode(VELOCIDAD, OUTPUT);
  pinMode(DIRPIN_1, OUTPUT);
  pinMode(DIRPIN_2, OUTPUT);

  pinMode(LEDROJO, OUTPUT);
  pinMode(LEDVERDE, OUTPUT);
  pinMode(LEDAZUL, OUTPUT);

  pinMode(POT, INPUT);

  Wire.begin(SDA,SCL);
  lcd.init();
  lcd.backlight();
  lcd.clear();
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
  lcd.clear();
  switch (estadoNuevo) {
    case PARO:
      Serial.println("Motor parado.");
      escribeLCD("Velocidad"+String(leerPot()),1);
      analogWrite(VELOCIDAD, 0);
      digitalWrite(LEDROJO, HIGH);
      digitalWrite(LEDAZUL, LOW);
      digitalWrite(LEDVERDE, LOW);
      lcd.clear();
      escribeLCD("Motor parado", 0);
       break;
    case DERECHA:
      Serial.println("Girando en una direccion.");
      escribeLCD("Giro Der. ", 0);
      escribeLCD("Velocidad: "+String(leerPot()),1);
      analogWrite(VELOCIDAD, leerPot());
      digitalWrite(DIRPIN_1, LOW);
      digitalWrite(DIRPIN_2, HIGH);
      digitalWrite(LEDROJO, LOW);
      digitalWrite(LEDVERDE, HIGH);
      digitalWrite(LEDAZUL, LOW);
      break;
    case IZQUIERDA:
      Serial.println("Girando en otra direccion.");
      escribeLCD("Giro IZQ", 0);
      escribeLCD("Velocidad: "+String(leerPot()),1);
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

void escribeLCD(String mensaje,int fila){
  // lcd.clear();
  lcd.setCursor(0,fila);
  lcd.print(mensaje);
}