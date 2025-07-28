
#define VELOCIDAD 14 
#define DIRPIN_1 12
#define DIRPIN_2 13

void setup() {
  Serial.begin(115200);

  pinMode(VELOCIDAD, OUTPUT);
  pinMode(DIRPIN_1,OUTPUT);
  pinMode(DIRPIN_2,OUTPUT);
}

void loop() {
  Serial.println("Girando en una direccion.");
  // digitalWrite(VELOCIDAD,HIGH); //Encendemos el motor
  analogWrite(VELOCIDAD, 70); 
  digitalWrite(DIRPIN_1,0);
  digitalWrite(DIRPIN_2,1);
  delay(5000);

Serial.println("Motor parado.");
  analogWrite(VELOCIDAD, 0);
  // digitalWrite(VELOCIDAD,LOW); //Apagamos el motor
  delay(2000);

  Serial.println("Girando en otra direccion.");
  // digitalWrite(VELOCIDAD,HIGH); //Encendemos el motor 
  analogWrite(VELOCIDAD, 70);
  digitalWrite(DIRPIN_1,1);
  digitalWrite(DIRPIN_2,0);
  delay(5000);

Serial.println("Motor parado.");
analogWrite(VELOCIDAD, 0);
  // digitalWrite(VELOCIDAD,LOW);
  delay(2000);
}
