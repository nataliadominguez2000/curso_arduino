#include <WiFi.h>  //Incluye la libreria necesaria para manejar conexiones WiFi
#include <WebServer.h>

#define LEDPIN 15
bool ledEncendido = false;
char* ssid = "Aula 1";
char* pwd = "Horus.2025";

WebServer servidor(80);

//Paginas

String home = R"rawliteral(
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
  <p>Estado del LED: <strong>%ESTADO%</strong></p>
  <form action="/toggle" method="POST">
    <button class="btn" type="submit">Encender/Apagar</button>
  </form>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);
  WiFi.mode(WIFI_STA);  //Configura el ESP32 como cliente WIFI
  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\n");
  Serial.print("Conectado a la IP: ");
  Serial.println(WiFi.localIP());

  //solicitudes web
  servidor.on("/", handle_OnConnect);  // No esta llamando a la funcion, si no que se ejecuta cuando pasa esto
 servidor.on("/toggle", HTTP_POST, handle_ToggleLED);
  servidor.begin();
  Serial.println("Servidor web iniciado");
}

void loop() {
  
  servidor.handleClient(); //Escucha las peticiones de los clientes al servidor
}

//Funcion de respuesta a las paginas web
void handle_OnConnect(){
  String estadoLED = ledEncendido ? "ENCENDIDO" : "APAGADO";
  String pagina = home;
  pagina.replace("%ESTADO%",estadoLED);
  servidor.send(200,"text/html",pagina); //Esta diciendo que el texto que hay en la variable home va a ser un texto estilo html si esta todo ok
}
void handle_ToggleLED(){
  ledEncendido = !ledEncendido;
  digitalWrite(LEDPIN, ledEncendido ? HIGH:LOW);
  Serial.print(ledEncendido ? "LED ENCENDIDO":"LED APAGADO");

  servidor.sendHeader("Location", "/");
  servidor.send(303);

}
