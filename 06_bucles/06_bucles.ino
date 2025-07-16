void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  delay(500);

  //Bucles controlados por un contador => for
  /*
  //De 0 a 10 de 1 en 1
   for(int i = 0; i <= 10 ; i++){
     Serial.println( "Numero: "+String(i));
     delay(1000);
   }
  */

  /*
  //De 0 a 100 de 2 en 2
   for(int i = 0; i <= 100; i += 2){
     Serial.println( "Numero: "+String(i));
     delay(1000);
   }
  */

  //De 100 a 0 de 1 en 1
  /*
  for(int i = 100; i >= 0; i-- ){
     Serial.println( "Numero: "+String(i));
   }
  */

  /*
String salida = "";

//Bucles en dos dimensiones
  for(int fila = 0; fila <= 10; fila ++ ){
    for(int columna = 0; columna <= 10; columna ++) {
      salida += String(fila)+":"+String(columna) + "\t";
    }
    salida += "\n";
  }

  Serial.print(salida);
  */

  //Bucles infinitos
  
  int limite = 10;
  int contador = 0; 
  /*
  for(;;){
    Serial.print("Infinito: ");
    Serial.println(contador);
    contador ++;

    if(contador == limite){
      break;
    }
  }
 */
  //Bucles while
  while (contador < limite) {
  Serial.print("While : ");
    Serial.println(contador);
    contador ++;
  }

}

void loop() {
  // put your main code here, to run repeatedly:
}
