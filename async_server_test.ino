#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"
#include "index.h"

// Set your access point network credentials
const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";

//relay pin number
int relay = 4;
int ledr = 16;
int ledg = 14;
int ledb = 12;
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println();
  pinMode(relay,OUTPUT);
  pinMode(ledr,OUTPUT);
  pinMode(ledg,OUTPUT);
  pinMode(ledb,OUTPUT);
  
  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });
  
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html",index_html);
    digitalWrite(relay,LOW);
    Serial.println("Relay On");
  });
  
    server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html",index_html);
    digitalWrite(relay,HIGH);
    Serial.println("Relay Off");
  });
  
    server.on("/color", HTTP_GET, [](AsyncWebServerRequest *request){
      int redval;
      int blueval;
      int greenval;
    redval = request->getParam("red")->value().toInt();
    Serial.println(redval);
    greenval = request->getParam("green")->value().toInt();
    Serial.println(greenval);
    blueval = request->getParam("blue")->value().toInt();
    Serial.println(blueval);

    digitalWrite(ledr,redval);
    digitalWrite(ledg,greenval);
    digitalWrite(ledb,blueval);
    request->send_P(200, "text/html",index_html);
    

  });
  // Start server
  server.begin();
}
 
void loop(){
  
}
