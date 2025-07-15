int dia= 9 ;
String nombreDia = "";
int nota = 8;
String calif = "";
void setup() {

  Serial.begin(115200);
  delay(500);
  
  // // put your setup code here, to run once:
  switch (dia) {
  case 1: 
  nombreDia = "El dia es Lunes";
  break;
  case 2:
  nombreDia = "El dia es Martes";
  break;
   case 3: 
  nombreDia = "El dia es Miercoles";
  break;
   case 4: 
  nombreDia = "El dia es Jueves";
  break;
   case 5: 
  nombreDia = "El dia es Viernes";
  break;
   case 6: 
  nombreDia = "El dia es Sabado";
  break;
   case 7: 
  nombreDia = "El dia es Domingo";
  break;
  default:
  nombreDia="NO es ningun dia de la semana";
  break;
  }

  Serial.println(nombreDia);
// --------------------------------------------------------------------------------------------
switch (nota) {
  case 1:
  case 2:
  case 3:
  case 4:
  calif = "Suspenso";
  case 5 ... 6: 
  calif ="Aprobado";
  break;
  case 7 ... 8: 
  calif ="Notable";
  break;
  default: 
  calif ="Sobresaliente ";
  break;
}

Serial.println("La nota es "+ calif);

}

void loop() {
  // put your main code here, to run repeatedly:

}
