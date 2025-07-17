#define ROJO 13
#define VERDE 12
#define AZUL 14

#define POT_R 4
#define POT_V 15
#define POT_A 2

int pot_r, pot_a, pot_v;
int led_r, led_a, led_v;

void setup() {

  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(ROJO, OUTPUT);
  pinMode(VERDE, OUTPUT);
  pinMode(AZUL, OUTPUT);

  pinMode(POT_A, INPUT);
  pinMode(POT_V, INPUT);
  pinMode(POT_R, INPUT);
}

void loop() {
  pot_r = analogRead(POT_R);
  led_r = map(pot_r, 0, 4096, 0, 255);
  analogWrite(ROJO, 255 - pot_r);

  pot_v = analogRead(POT_V);
  led_v = map(pot_v, 0, 4096, 0, 255);
  analogWrite(VERDE, 255 -pot_v);

  pot_a = analogRead(POT_A);
  led_a = map(pot_a, 0, 4096, 0, 255);
  analogWrite(AZUL, 255 - pot_a);
  
  delay(500);
}
