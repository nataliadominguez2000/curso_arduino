int numeros[6];
int otro[]={1,2,3,4,5,6};

int sizeNumeros = 0;
int sizeOtro = 0;
void setup() {

  Serial.begin(115200);
  sizeNumeros = sizeof(numeros) / sizeof(numeros[0]);
  sizeOtro = sizeof(otro) / sizeof(otro[0]);
  // put your setup code here, to run once:
  for(int i = 0; i <= sizeOtro; i ++){
    numeros[i] = otro[i];
  }
  for(int i = 0; i< sizeNumeros ; i++){
    Serial.print("numero "+ String(i)+" es : "+numeros[i]+"\n");
  }
 
}

void loop() {
  // put your main code here, to run repeatedly:

}
