#include <Wire.h>
#define SDA 13
#define SCL 14

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(100);
  // byte count = 0;

  Wire.begin(SDA,SCL);
  for(byte i= 0;i< 120;i++){
    Wire.beginTransmission(i);
    if(Wire.endTransmission() == 0){
      Serial.print("Direccion encontrada: ");
      // Serial.print(i,DEC);
      Serial.print(" 0x");
      Serial.println(i,HEX);
      // count++;
      delay(10);
    }
  }
  // Serial.print("\n");
  // Serial.println("Encontrados "+String(count));
}

void loop() {
  // put your main code here, to run repeatedly:

}
