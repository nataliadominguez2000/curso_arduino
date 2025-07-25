#include <ESP32Servo.h>  // Incluye la librería específica para manejar servos con el ESP32  (Buscala en el gestor de biblioteca y es el de Kevin Harrington,John K. Bennett)
#include <BluetoothSerial.h>

#define PINSERVER 15  // Define el pin GPIO 15 como el pin de control del servo
#define LEDROJO 13
#define LEDVERDE 14

Servo miServo;  // Crea un objeto de tipo Servo
BluetoothSerial serialBT;

String entrada = "";
String secreto = "1234";
bool primeraVez = true;

void setup() {

  Serial.begin(115200);
  // Configura la frecuencia del servo a 50 Hz (frecuencia estándar para servos)

  //Declaracion de los pines de los colores
  pinMode(LEDROJO, OUTPUT);
  pinMode(LEDVERDE, OUTPUT);

  //Bluetooth
  serialBT.begin("Caja_Fuerte_Natalia");
  miServo.setPeriodHertz(50);

  // Asocia el pin PINSERVER al objeto servo con un rango de pulsos de 500 a 2500 microsegundos
  // Esto define el rango de movimiento del servo (puede variar según el modelo)
  miServo.attach(PINSERVER, 500, 2500);
  digitalWrite(LEDROJO, HIGH);
  digitalWrite(LEDVERDE, LOW);
  miServo.write(0);
}

void loop() {
  if (primeraVez) {
    Serial.println("Introduzca la clave.");
    primeraVez = false;
  }
  if (Serial.available()) {
    entrada = Serial.readStringUntil('\n');
    entrada.trim();
    if (entrada == secreto) {
      Serial.println("Clave correcta");
      miServo.write(90);
      digitalWrite(LEDROJO, LOW);
      digitalWrite(LEDVERDE,HIGH);
      delay(5000);
      Serial.println("Puerta Cerrada");
      miServo.write(0);
      digitalWrite(LEDVERDE, LOW);
      digitalWrite(LEDROJO,HIGH);
    } else {
      Serial.println("Clave incorrecta,Pruebe otra vez..");
    }
    Serial.println("Introduzca la clave");
  }
}
