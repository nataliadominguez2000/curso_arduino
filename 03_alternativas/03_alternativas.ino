/*
PROGRAMACION ESTRUCTURADA
--------------------------
- Secuencia
- Alternativa
- Repeticion
*/
// int edad = 12;
int nota = 4;
void setup() {
  // operando -> operador -> operando
  //OR -> ||
  //AND -> &&
  //NOT -> !

  Serial.begin(115200);
  delay(1000);
  Serial.println("La nota final es:");

  if(nota < 5){
    Serial.println("Suspenso");
  }else if(nota >= 5 && nota < 7) {
    Serial.println("Aprobado");
  }else if(nota >= 7 && nota < 9){
    Serial.println("Notable");
  }else{
    Serial.println("Sobresaliente");
  }

}

void loop() {
  /*
  if(Serial.available() >= 0){
    //Si está disponible el Serial
    edad  = Serial.read(); //Leo lo que pone en el Serial
  }

 if(edad >= 18){
    //Si se cumple
    Serial.println("La persona es mayor de edad");
  }else {
    //Si no se cumple
    Serial.println("La persona es menor de edad");
  }
  delay(10000);*/

  
}
