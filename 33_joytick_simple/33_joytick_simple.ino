#define PIN_X 13
#define PIN_Y 12
#define PIN_SW 14

// Ajusta según placa: Arduino UNO = 512, ESP32 = 2048
const int centro = 2048;
const int margen = 300;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_X, INPUT);
  pinMode(PIN_Y, INPUT);
  pinMode(PIN_SW, INPUT_PULLUP);

  Serial.println("Joystick listo");
}

void loop() {
  int rawX = analogRead(PIN_X);
  int rawY = analogRead(PIN_Y);
  int boton = digitalRead(PIN_SW);

  int x = rawX - centro;
  int y = rawY - centro;

  bool movedX = abs(x) > margen;
  bool movedY = abs(y) > margen;

  String direccion = "";

  if (!movedX && !movedY) {
    direccion = "CENTRO";
  } else {
    if (movedX) {
      direccion += (x > 0) ? "DERECHA" : "IZQUIERDA";
    }
    if (movedY) {
      if (direccion != "") direccion += "-";
      direccion += (y > 0) ? "ARRIBA" : "ABAJO";
    }
  }

  Serial.print("Dirección: ");
  Serial.print(direccion);
  Serial.print(" | Botón: ");
  Serial.println(boton == LOW ? "PULSADO" : "SUELTO");

  delay(1000);
}
