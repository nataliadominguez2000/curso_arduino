#define SENSOR 32


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(SENSOR, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int lectura = touchRead(SENSOR);
Serial.println("Sensor: "+String(lectura));

delay(200);
}
