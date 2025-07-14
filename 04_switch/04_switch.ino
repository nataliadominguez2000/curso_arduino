int dia= 7;
String nombreDia = "";
void setup() {

  Serial.begin(115200);
  delay(500);
  
  // put your setup code here, to run once:
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
}

void loop() {
  // put your main code here, to run repeatedly:

}
