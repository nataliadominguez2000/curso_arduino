
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // Serial.println(sumaNumeros(5,8));
  Serial.print("Suma del array: ");
  int numeros[] = { 1, 3, 4, 5, 8, 12, 34 };
  int acumulador = 0;
  for (int i = 0; i < 7; i++) {
    acumulador = sumaNumeros(acumulador, numeros[i]);
  }
  Serial.println(acumulador);
  char cadena[] = "Hola Mundo";
  int longitud = longitudCadena(cadena);
  Serial.print("longitud cadena: ");
  Serial.println(longitud);
  Serial.print("longitud cadena: ");
  char* resultado;
  resultado = inversa(cadena);
  Serial.println(resultado);
}
void loop() {
  // put your main code here, to run repeatedly:
}
//FUNCIONES
//Funcion que suma dos numeros
int sumaNumeros(int num1, int num2) {
  int suma = num1 + num2;
  return suma;
}
//Funcion que devuelve el tamaño de una cadena
int longitudCadena(char cadena[]) {
  int i = 0;
  while (cadena[i] != '\0') {
    i++;
  }
  return i;
}

char* inversa(char* cadena) {
  int longitud = longitudCadena(cadena);
  char* temp = new char[longitud + 1];  // memoria dinámica, +1 para '\0'

  for (int i = 0; i < longitud; i++) {
    temp[longitud - i - 1] = cadena[i];
  }
  temp[longitud] = '\0';  // final de cadena

  return temp;  // recuerda liberar con delete[] luego
}