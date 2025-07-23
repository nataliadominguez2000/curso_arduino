#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

// -------- CONFIGURACIÓN --------
#define LEDPIN 2
#define DHTPIN 14
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
bool ledEncendido = false;

char* ssid = "Aula 1";
char* pwd = "Horus.2025";

WebServer servidor(80);

// -------- HTML --------
String home = "<!DOCTYPE html>"
              "<html lang=\"es\">"
              "<head>"
              "<meta charset=\"UTF-8\">"
              "<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">"
              "<title>Página Principal</title>"
              "</head>"
              "<body>"
              "<h1>Hola Mundo</h1>"
              "<h2>Esta es la primera página</h2>"
              "<a href=\"/segunda\">Ir a la segunda página</a><br><br>"
              "<a href=\"/led\">Controlar LED</a><br><br>"
              "<a href=\"/sensor\">Ver temperatura y humedad</a>"
              "</body>"
              "</html>";

String home2 = "<!DOCTYPE html>"
               "<html lang=\"es\">"
               "<head>"
               "<meta charset=\"UTF-8\">"
               "<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">"
               "<title>Segunda Página</title>"
               "</head>"
               "<body>"
               "<h1>Esta es la segunda página</h1>"
               "</body>"
               "</html>";

String ledPage = "<!DOCTYPE html>"
                 "<html lang=\"es\">"
                 "<head>"
                 "<meta charset=\"UTF-8\">"
                 "<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">"
                 "<title>Control LED</title>"
                 "<style>"
                 "body { font-family: Arial; text-align: center; padding-top: 50px; }"
                 ".btn {"
                 "  font-size: 20px;"
                 "  padding: 15px 30px;"
                 "  color: white;"
                 "  background-color: #007BFF;"
                 "  border: none;"
                 "  border-radius: 10px;"
                 "  cursor: pointer;"
                 "}"
                 ".btn:hover { background-color: #0056b3; }"
                 "</style>"
                 "</head>"
                 "<body>"
                 "<h1>Control del LED</h1>"
                 "<p>Estado del LED: <strong>%ESTADO%</strong></p>"
                 "<form action=\"/toggle\" method=\"POST\">"
                 "<button class=\"btn\" type=\"submit\">Encender/Apagar</button>"
                 "</form>"
                 "</body>"
                 "</html>";

String sensorPage = "<!DOCTYPE html>"
                    "<html lang=\"es\">"
                    "<head>"
                    "<meta charset=\"UTF-8\">"
                    "<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">"
                    "<title>Sensor DHT22</title>"
                    "<style>"
                    "body { font-family: Arial; text-align: center; padding-top: 50px; }"
                    "</style>"
                    "</head>"
                    "<body>"
                    "<h1>Lectura de Sensor</h1>"
                    "<p>Temperatura actual: <strong>%TEMPERATURA%</strong> ºC</p>"
                    "<p>Humedad actual: <strong>%HUMEDAD%</strong> %</p>"
                    "</body>"
                    "</html>";



// -------- SETUP --------
void setup() {
  Serial.begin(115200);
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);
  dht.begin();

  // Conexión WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado a la IP: " + WiFi.localIP().toString());

  // Rutas
  servidor.on("/", handle_Home);
  servidor.on("/segunda", handle_Second);
  servidor.on("/led", handle_LEDPage);
  servidor.on("/sensor", handle_SensorPage);
  servidor.on("/toggle", HTTP_POST, handle_ToggleLED);

  servidor.begin();
  Serial.println("Servidor web iniciado");
}

// -------- LOOP --------
void loop() {
  servidor.handleClient();
}

// -------- RUTAS --------
void handle_Home() {
  servidor.send(200, "text/html", home);
}

void handle_Second() {
  servidor.send(200, "text/html", home2);
}

void handle_LEDPage() {
  String estado = ledEncendido ? "ENCENDIDO" : "APAGADO";
  String pagina = ledPage;
  pagina.replace("%ESTADO%", estado);
  servidor.send(200, "text/html", pagina);
}

void handle_SensorPage() {
  float temperatura = dht.readTemperature();
  float humedad = dht.readHumidity();

  String tempTexto = isnan(temperatura) ? "Error" : String(temperatura, 1);
  String humTexto = isnan(humedad) ? "Error" : String(humedad, 1);

  String pagina = sensorPage;
  pagina.replace("%TEMPERATURA%", tempTexto);
  pagina.replace("%HUMEDAD%", humTexto);
  servidor.send(200, "text/html", pagina);
}

void handle_ToggleLED() {
  ledEncendido = !ledEncendido;
  digitalWrite(LEDPIN, ledEncendido ? HIGH : LOW);
  Serial.println(ledEncendido ? "LED ENCENDIDO" : "LED APAGADO");

  servidor.sendHeader("Location", "/led");
  servidor.send(303);
}
