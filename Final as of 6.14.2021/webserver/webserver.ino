#include <FastLED.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "index.h"

const char* ssid = "ESP8266-Access-Point";
const char* password = "123456789";
const int shutoff = 22;
const int led = 23;
const int forward = 21;
const int numled = 37;
int lastMillis = 0;
int iAnimStep = 0;
int color0 = 0;
int color1 = 0;
bool color_changing = false;



CRGB leds[numled];

AsyncWebServer server(80);

void setup() {
  FastLED.addLeds<WS2812B, led, GRB>(leds, numled);
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(shutoff, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(forward, OUTPUT);
  WiFi.softAP(ssid, password);
  digitalWrite(shutoff, HIGH); //turning car on

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
  });
  //shutoff on
  server.on("/on", HTTP_POST, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
    digitalWrite(shutoff, LOW); //turns car off
    //write relay low
  });
  //shutoff off
  server.on("/off", HTTP_POST, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
    digitalWrite(shutoff, HIGH);
    //write relay high
  });

  //forward
  server.on("/forward", HTTP_POST, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
    digitalWrite(forward, HIGH);
    //write relay high to make cart go forward
  });

  server.on("/stop", HTTP_POST, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
    digitalWrite(forward, LOW);
    Serial.println("Relay Off");
    //write relay low to make car stop
  });

  server.on("/color", HTTP_POST, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
    Serial.println("Color recieved");
    color_changing = true;
    Serial.println(request->url());
    Serial.println(request->getParam("color", true /* isPost */)->value());
    const int irate = 37;
    color0 = strtol(&(request->getParam("color", true /* isPost */)->value().c_str()[1]), 0,  16);
    color1 = color0;
    for (int i = 0; i < irate; i++) {
      leds[i] = color0;
      delay(50);
      FastLED.show();

    }
    color_changing = false;
  });

  server.on("/4july", HTTP_POST, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
    color0 = 0xFF0000;//red
    color1 = 0x0000FF; //blue
  });

  server.on("/hawks", HTTP_POST, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
    color0 = 0x00FF00;//green
    color1 = 0x0000FF; //blue
  });

  server.on("/xmas", HTTP_POST, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
    color0 = 0xFF0000;
    color1 = 0xFFFFFF;
  });

  server.on("/scroll", HTTP_POST, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
    Serial.println("Color recieved");
    const int irate = 37;
    color0 = strtol(&(request->getParam("scroll0", true /* isPost */)->value().c_str()[1]), 0,  16);
    color1 = strtol(&(request->getParam("scroll1", true /* isPost */)->value().c_str()[1]), 0,  16);
  });

  server.begin();
  lastMillis = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  int millisNow = millis();

  if (lastMillis + 300 > millisNow)
    return;

  lastMillis = millisNow;

  if (color_changing)
    return;

  for (int i = 0; i < numled; i++)
  {
    switch (((i + iAnimStep) / 4) % 2)
    {
      case 0:
        leds[i] = color0;
        break;
      case 1:
        leds[i] = color1;
        break;
    }
  }
  FastLED.show();
  iAnimStep = (++iAnimStep ) % 9; // 0->3

}
