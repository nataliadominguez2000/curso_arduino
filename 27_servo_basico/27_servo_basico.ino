#include <ESP32Servo.h>   // Incluye la librería específica para manejar servos con el ESP32  (Buscala en el gestor de biblioteca y es el de Kevin Harrington,John K. Bennett)

#define PINSERVER 15      // Define el pin GPIO 15 como el pin de control del servo 

Servo miServo;            // Crea un objeto de tipo Servo
int posValor = 0;         // Variable que almacena la posición del servo (de 0 a 180 grados)

void setup() {
  // Configura la frecuencia del servo a 50 Hz (frecuencia estándar para servos)
  miServo.setPeriodHertz(50);

  // Asocia el pin PINSERVER al objeto servo con un rango de pulsos de 500 a 2500 microsegundos
  // Esto define el rango de movimiento del servo (puede variar según el modelo)
  miServo.attach(PINSERVER, 500, 2500);
}

void loop() {
  // // Primer bucle: mueve el servo desde 0° hasta 180° en pasos de 1 grado
  // for (posValor = 0; posValor <= 180; posValor += 1) {
  //   miServo.write(posValor);  // Envía la posición al servo
  //   delay(20);                // Espera 20 milisegundos para que el servo se mueva
  // }
  // delay(200);
  // // Segundo bucle: mueve el servo desde 180° de vuelta hasta 0° en pasos de 1 grado
  // for (posValor = 180; posValor >= 0; posValor -= 1) {
  //   miServo.write(posValor);  // Envía la posición al servo
  //   delay(20);                // Espera 20 milisegundos para que el servo se mueva
  // }
  // delay(200);

  //Ahora que gire de 45 a 45 º

  for(posValor = 0 ; posValor <= 180 ;posValor += 45){
    miServo.write(posValor);
    delay(500);
  }
  delay(500);
  for (posValor=180; posValor >= 0; posValor -= 45) {
    miServo.write(posValor);
    delay(500);
  }
  delay(500);
}
