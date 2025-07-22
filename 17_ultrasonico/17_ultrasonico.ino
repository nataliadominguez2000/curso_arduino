#define TRG 13
#define ECHO 14
#define LED 15
#define MAX_DIST 700 // cm

float distancia = 0.0;
float timeOut = MAX_DIST * 60;
int volSonido = 340;

int valorLed = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(TRG,OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  distancia = getSonar();
  Serial.println("Distance: "+String(distancia)+"cm");

  valorLed = map(distancia,0,300,0,255);
  
  analogWrite(LED, 255 - valorLed);
  delay(500);

}

float getSonar() {
  unsigned long int pingTime;
  float dist = 0.0;
  digitalWrite(TRG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRG, LOW);
  pingTime = pulseIn(ECHO, HIGH, timeOut);
  Serial.println("Ping Time : "+String(pingTime));
  dist = (float)pingTime * volSonido / 2 / 10000;
  return dist;
}