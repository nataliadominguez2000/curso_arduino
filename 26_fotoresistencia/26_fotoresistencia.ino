#define FOTO_PIN 4     // Pin donde está conectada la fotorresistencia (LDR)
#define LED 2          // Pin del LED (integrado en la placa ESP32)

int valorLuz = 0;       // Variable para guardar la lectura del sensor
int valorLed = 0;       // Valor que se enviará al LED (PWM)

void setup() {
  pinMode(FOTO_PIN, INPUT);   // Configurar el pin del LDR como entrada
  pinMode(LED, OUTPUT);       // Configurar el LED como salida
  Serial.begin(115200);         // Iniciar monitor serie para depuración
}

void loop() {
  // Leer valor de la fotorresistencia (0 a 4095 en ESP32)
  valorLuz = analogRead(FOTO_PIN);

  // Invertir valor para que cuando haya más oscuridad, el LED brille más
  valorLed = map(valorLuz, 0, 4095,255,0);

  // Escribir el valor PWM al LED (ajusta su brillo)
  analogWrite(LED, valorLed); // En ESP32 se puede usar ledcWrite si no funciona

  // Mostrar valores por el monitor serie
  Serial.print("Luz: ");
  Serial.print(valorLuz);
  Serial.print(" | LED: ");
  Serial.println(valorLed);



  delay(500); // Pequeña pausa
}

