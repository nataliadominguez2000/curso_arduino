#define PIN_X 13
#define PIN_Y 12
#define PIN_SW 14

#define ARRIBA 0
#define ABAJO 2
#define DERECHA 4
#define IZQUIERDA 5

// Cambia esto según tu placa:
// Para Arduino UNO usa: const int centro = 512;
// Para ESP32 usa: const int centro = 2048;
const int centro = 2048;
const int margen = 300; // Margen muerto

int brujula[] = {ARRIBA,ABAJO,DERECHA,IZQUIERDA};

void setup() {
  Serial.begin(115200);
  pinMode(PIN_X, INPUT);
  pinMode(PIN_Y, INPUT);
  pinMode(PIN_SW, INPUT_PULLUP);

  // pinMode(LED_ARRIBA,OUTPUT);
  // pinMode(LED_ABAJO,OUTPUT);
  // pinMode(LED_DERECHA,OUTPUT);
  // pinMode(LED_IZQUIERDA,OUTPUT);
for(int i = 0; i < 4; i++){
  pinMode(brujula[i], OUTPUT);
}
  Serial.println("Joystick listo");
}

void loop() {
  int rawX = analogRead(PIN_X);
  int rawY = analogRead(PIN_Y);
  int boton = digitalRead(PIN_SW);

  int x = rawX - centro;
  int y = rawY - centro;

  //Evaluamos el eje Y
  bool left = x < -margen;
  bool right = x > margen;

  bool up = y > margen;
  bool down = y < -margen;
  apagarLed();
  String direccion = "";

 if (!left && !right && !up && !down) {
    direccion = "CENTRO";
    
  } else {
    if (up) {
      digitalWrite(brujula[0], HIGH);
      direccion += "ARRIBA";
    }
    if (down) {
      digitalWrite(brujula[1], HIGH);
      direccion += "ABAJO";
    }
    if (left) {
      digitalWrite(brujula[3], HIGH);
      if (direccion.length() > 0) direccion += "-";
      direccion += "IZQUIERDA";
    }
    if (right) {
      digitalWrite(brujula[2], HIGH);
      if (direccion.length() > 0) direccion += "-";
      direccion += "DERECHA";
    }
  }
  Serial.print("Dirección: ");
  Serial.print(direccion);
  Serial.print(" | Botón: ");

  if(boton == LOW){
     Serial.println("0 (presionado)");
    encenderLed();
  }else{
    Serial.println("1 (no presionado)");
  }
 
  delay(200);
}

//Funcion que apaga todos los LED sin tener que hacerlo todas las veces
void apagarLed(){
for(int i = 0; i < 4; i++){
  digitalWrite(brujula[i], LOW);
}
}

//Funcion que enciende los LEDs sin tener que hacerlo todas las veces
void encenderLed(){
  for(int i = 0; i < 4; i ++){
    digitalWrite(brujula[i], HIGH);
  }
}