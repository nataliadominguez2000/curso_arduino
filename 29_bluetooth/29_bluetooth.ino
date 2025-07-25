#include <BluetoothSerial.h>

BluetoothSerial serialBT;

void setup() {
  Serial.begin(115200);
  serialBT.begin("BT_Natalia",true);
  Serial.println("Dispositivo listo para emparejarse");

}

void loop() {
  
  if(Serial.available()){
    serialBT.write(Serial.read());
  }
  if(serialBT.available()){
    Serial.write(serialBT.read());
  }
  delay(500);
}
