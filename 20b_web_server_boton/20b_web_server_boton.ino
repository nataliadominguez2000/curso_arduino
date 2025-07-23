#include <WiFi.h>           // Librería para manejo de WiFi
#include <WebServer.h>      // Librería para crear el servidor web

#define LEDPIN 2
bool ledEncendido = false;

// Credenciales de WiFi
char* ssid = "Aula 1";
char* pwd = "Horus.2025";

WebServer servidor(80);  // Puerto HTTP

// ====== Contenido HTML de las páginas ======
String home = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width,initial-scale=1">
  <title>Página Principal</title>
</head>
<body>
  <h1>Hola Mundo</h1>
  <h2>Esta es la primera página</h2>
  <a href="/segunda">Ir a la segunda página</a><br><br>
  <a href="/led">Ir a la página encender LED</a>
</body>
</html>
)rawliteral";

String home2 = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width,initial-scale=1">
  <title>Segunda Página</title>
</head>
<body>
  <h1>Esta es la segunda página</h1>
</body>
</html>
)rawliteral";

String led = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width,initial-scale=1">
  <title>Control LED</title>
  <style>
    body { font-family: Arial; text-align: center; padding-top: 50px; }
    h1 { color: #333; }
    .btn {
      font-size: 20px;
      padding: 15px 30px;
      color: white;
      background-color: #007BFF;
      border: none;
      border-radius: 10px;
      cursor: pointer;
    }
    .btn:hover {
      background-color: #0056b3;
    }
  </style>
</head>
<body>
  <h1>Control del LED</h1>
  <form action="/toggle" method="POST">
    <button class="btn" type="submit">Encender/Apagar</button>
  </form>
</body>
</html>
)rawliteral";

// ====== Setup ======
void setup() {
  Serial.begin(115200);
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);

  // Conexión WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado a la IP: " + WiFi.localIP().toString());

  // Rutas del servidor
  servidor.on("/", handle_Home);
  servidor.on("/segunda", handle_Second);
  servidor.on("/led", handle_LEDPage);
  servidor.on("/toggle", HTTP_POST, handle_ToggleLED);

  servidor.begin();
  Serial.println("Servidor web iniciado");
}

// ====== Loop ======
void loop() {
  servidor.handleClient();
}

// ====== Manejadores de rutas ======
void handle_Home() {
  servidor.send(200, "text/html", home);
}

void handle_Second() {
  servidor.send(200, "text/html", home2);
}

void handle_LEDPage() {
  String pagina = led;
  servidor.send(200, "text/html", pagina);
}

void handle_ToggleLED() {
  // Cambiar estado del LED
  ledEncendido = !ledEncendido;
  digitalWrite(LEDPIN, ledEncendido ? HIGH : LOW);
  Serial.println(ledEncendido ? "LED ENCENDIDO" : "LED APAGADO");

  // Redirigir de nuevo a la página del LED
  servidor.sendHeader("Location", "/led");
  servidor.send(303);
}
