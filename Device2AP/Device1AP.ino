#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "park_device2";
const char* password = "123456789";
const char indexsource[] =
  "<!DOCTYPE HTML>"
  "<html>"
  "<head>"
  "<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
  "<titleETRI REMOTE SERVER</title>"
  "<style>"
  "\"body { background-color: #808080; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }\""
  ".button {background-color: #4CAF50;border: none;color: white;padding: 15px 32px;text-align: center;text-decoration: none;display: inline-block;font-size: 16px;}"
  "</style>"
  "</head>"
  "<body>"
  "<h1>ETRI Device1</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<P>"
  "<INPUT type=\"button\" class=\"button\" onclick=\"location.href='/device1_1'\" value=\"device1_1\">"
  "<INPUT type=\"button\" class=\"button\" onclick=\"location.href='/device1_2'\" value=\"device1_2\">"
  "</P>"
  "</FORM>"
  "</body>"
  "</html>";

const char device1_1[] =
  "<!DOCTYPE HTML>"
  "<html>"
  "<head>"
  "<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
  "<titleETRI REMOTE SERVER</title>"
  "<style>"
  "\"body { background-color: #808080; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }\""
  "</style>"
  "</head>"
  "<body>"
  "<h1>Debice1_1</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<P>"
  "</P>"
  "</FORM>"
  "</body>"
  "</html>";


const char device1_2[] =
  "<!DOCTYPE HTML>"
  "<html>"
  "<head>"
  "<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
  "<titleETRI REMOTE SERVER</title>"
  "<style>"
  "\"body { background-color: #808080; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }\""
  "</style>"
  "</head>"
  "<body>"
  "<h1>Debice1_2</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<P>"
  "</P>"
  "</FORM>"
  "</body>"
  "</html>";

ESP8266WebServer server(80); //port 80

void indexpg() {
  server.send(200, "text/html", indexsource);
}

void de1() {
  server.send(200, "text/html", device1_1);
}

void de2() {
  server.send(200, "text/html", device1_2);
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", indexpg);
  server.on("/device1_1", de1);
  server.on("/device1_2", de2);
  server.begin();
  Serial.println("-----------ETRI REMOTE Server Started--------");
}

void loop() {
  server.handleClient();
}
