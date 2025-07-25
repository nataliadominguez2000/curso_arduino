#include <ESP32Servo.h>   // Incluye la librería específica para manejar servos con el ESP32  (Buscala en el gestor de biblioteca y es el de Kevin Harrington,John K. Bennett)

#define PINSERVER 15      // Define el pin GPIO 15 como el pin de control del servo 

Servo miServo;            // Crea un objeto de tipo Servo

String entrada = "";
String secreto = "1234";
bool primeraVez = true;

void setup() {

  Serial.begin(115200);
  // Configura la frecuencia del servo a 50 Hz (frecuencia estándar para servos)
  miServo.setPeriodHertz(50);

  // Asocia el pin PINSERVER al objeto servo con un rango de pulsos de 500 a 2500 microsegundos
  // Esto define el rango de movimiento del servo (puede variar según el modelo)
  miServo.attach(PINSERVER, 500, 2500);

  miServo.write(0);
  
}

void loop() {
  if(primeraVez){
    Serial.println("Introduzca la clave.");
    primeraVez = false;
  }
  if(Serial.available() > 0){
    entrada = Serial.readStringUntil('\n');
    entrada.trim();
    if(entrada == secreto){
      Serial.println("Clave correcta");
      miServo.write(90);
      delay(5000);
      Serial.println("Puerta Cerrada");
      miServo.write(0);
    }else {
      Serial.println("Clave incorrecta,Pruebe otra vez..");
    }
  }

}
