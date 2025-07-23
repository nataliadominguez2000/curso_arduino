#include <WiFi.h>  //Incluye la libreria necesaria para manejar conexiones WiFi
#include <WebServer.h>

char* ssid = "Aula 1";
char* pwd = "Horus.2025";

WebServer servidor(80);

//Paginas

String home = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width,initial-scale=1\"><title>Document</title></head><body><h1>Hola Mundo</h1><h2>Esta es la primera pagina</h2><a href=\"/segunda\">Ir a la segunda página</a></body></html>";
String home2 = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width,initial-scale=1\"><title>Segunda Pagina</title></head><body><h1>Esta es la segunda pagina</h1></body></html>";

void setup() {
  Serial.begin(115200);
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
  servidor.on("/", handle_OnConnect); 
  servidor.on("/segunda",handle_OnConnect2); // No esta llamando a la funcion, si no que se ejecuta cuando pasa esto
  servidor.begin();
  Serial.println("Servidor web iniciado");
}

void loop() {
  
  servidor.handleClient(); //Escucha las peticiones de los clientes al servidor
}

//Funcion de respuesta a las paginas web
void handle_OnConnect(){

  servidor.send(200,"text/html",home); //Esta diciendo que el texto que hay en la variable home va a ser un texto estilo html si esta todo ok
}
void handle_OnConnect2(){

  servidor.send(200,"text/html",home2); //Esta diciendo que el texto que hay en la variable home va a ser un texto estilo html si esta todo ok
}