#define TRG 13
#define ECHO 14
#define LED 15
#define BUZZER 12
#define MAX_DIST 700  // cm

float distancia = 0.0;
float timeOut = MAX_DIST * 60;
int volSonido = 340;

int valorLed = 0;

int intervalos[] = {10,20,30,40,50,60,70,80,90,100};



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(TRG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER,OUTPUT);
}

void loop() {
  int umbral;
  // put your main code here, to run repeatedly:
  distancia = getSonar();
  umbral = getIntervalo(distancia);
  if(umbral <= 100){
    pitar(umbral);
  }
  Serial.println("Distance: " + String(distancia) + "cm");

  valorLed = 255 - map(distancia, 0, 300, 0, 255);

  analogWrite(LED, valorLed);
  delay(500);
}
//Calcula la distancia y el tiempo
float getSonar() {
  unsigned long int pingTime;
  float dist = 0.0;
  digitalWrite(TRG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRG, LOW);
  pingTime = pulseIn(ECHO, HIGH, timeOut);
  Serial.println("Ping Time : " + String(pingTime));
  dist = (float)pingTime * volSonido / 2 / 10000;
  return dist;
}

int getIntervalo(float lejos) {
  int salida = 1000;
  for(int i = 0; i < 10; i ++){
    if(lejos < intervalos[i]){
      salida = intervalos[i];
      break;
    }
  }
  return salida;
}

void pitar(int umbral){
  for(int i = 0; i < 5 ; i ++){
    digitalWrite(BUZZER,HIGH);
    delay(50);
    digitalWrite(BUZZER,LOW);
    delay(10 * umbral);
  }
}