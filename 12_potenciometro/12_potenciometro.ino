#define LED 13
#define POT 4

#define ZUM 14
#define POT2 12


int valorPot = 0;
int valorPotZ = 0;
int valorLed = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(ZUM, OUTPUT);
  pinMode(POT, INPUT);
  pinMode(POT2, INPUT);
}

void loop() {
  // 0 - 4096
  valorPot = analogRead(POT);
  valorPotZ = analogRead(POT2);

  valorLed = map(valorPot,0,4096,0,255);

  analogWrite(LED, valorLed);

  digitalWrite(ZUM, HIGH);
  delay(valorPotZ);

  digitalWrite(ZUM, LOW);
  delay(valorPotZ);

  Serial.println("Led: " +String(valorLed)+ " Pot: "+String(valorPot));
  Serial.println("Frecuencia: "+String(valorPotZ)+" Hz");
}
