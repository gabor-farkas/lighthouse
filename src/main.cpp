#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char *ssid = "UPC0082871";
const char *password = "ez3pdJexfxvZ";
const String html = "<style> * { box-sizing: border-box; } body { margin: 0; } div { display: flex; flex-direction: column; height: 100%; padding: 5vh; } a { border: 1px solid black; border-radius: 10vh; display: block; height: 100%; text-align: center; font-size: 20vh; text-decoration: none; color: black; line-height: 90vh; background: lightgray; } </style> <div> <a href=\"/toggle\">&#x1F4A1;</a> </div>";

ESP8266WebServer server(80);

int status;

void turnOn()
{
  server.send(200, "text/html", html);
  status = HIGH;
  digitalWrite(D0, status);
}

void turnOff()
{
  server.send(200, "text/html", html);
  status = LOW;
  digitalWrite(D0, status);
}

void toggle()
{
  server.send(200, "text/html", html);
  status = 1 - status;
  digitalWrite(D0, status);
}

void setup()
{
  pinMode(D0, OUTPUT);
  status = LOW;
  digitalWrite(D0, status);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
  }

  WiFi.localIP();

  MDNS.begin("esp8266");

  server.on("/", turnOn);
  server.on("/on", turnOn);
  server.on("/off", turnOff);
  server.on("/toggle", toggle);
  server.begin();
}

void loop()
{
  server.handleClient();
}