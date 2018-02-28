#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
IRsend irsend(4); // An IR LED is controlled by GPIO pin 4 (D2)

const char* ssid = "park_device1";
const char* password = "";
const char indexsource[] =
  "<!DOCTYPE HTML>"
  "<html>"
  "<head>"
  "<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
  "<titleETRI AirCon</title>"
  "<style>"
  "\"body { background-color: #808080; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }\""
  "</style>"
  "</head>"
  "<body>"
  "<h1>ETRI Aircon</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<div>"
  "<P>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt1'\" value=\"power\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt2'\" value=\"up\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt3'\" value=\"down\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt4'\" value=\"wind\"></INPUT>"
  "</P>"
  "</div>"
  "</FORM>"
  "</body>"
  "</html>";

const char power[] =
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
  "<h1>Aircon ON / OFF</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<div>"
  "<P>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt1'\" value=\"power\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt2'\" value=\"up\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt3'\" value=\"down\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt4'\" value=\"wind\"></INPUT>"
  "</P>"
  "</div>"
  "</FORM>"
  "</body>"
  "</html>";


const char temup[] =
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
  "<h1>Temp UP</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<div>"
  "<P>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt1'\" value=\"power\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt2'\" value=\"up\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt3'\" value=\"down\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt4'\" value=\"wind\"></INPUT>"
  "</P>"
  "</div>"
  "</FORM>"
  "</body>"
  "</html>";

const char temdown[] =
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
  "<h1>Temp Down</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<div>"
  "<P>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt1'\" value=\"power\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt2'\" value=\"up\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt3'\" value=\"down\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt4'\" value=\"wind\"></INPUT>"
  "</P>"
  "</div>"
  "</FORM>"
  "</body>"
  "</html>";

const char wind[] =
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
  "<h1>Select Wind</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<div>"
  "<P>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt1'\" value=\"power\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt2'\" value=\"up\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt3'\" value=\"down\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt4'\" value=\"wind\"></INPUT>"
  "</P>"
  "</div>"
  "</FORM>"
  "</body>"
  "</html>";

ESP8266WebServer server(8080); //port 8080

void indexpg() {
  server.send(200, "text/html", indexsource);
}

void button1() {
  server.send(200, "text/html", power);
  irsend.sendNEC(0x616A817E, 32);
}

void button2() {
  server.send(200, "text/html", temup);
  irsend.sendNEC(0x616A6996, 32);
}

void button3() {
  server.send(200, "text/html", temdown);
  irsend.sendNEC(0x616AE916, 32);
}

void button4() {
  server.send(200, "text/html", wind);
  irsend.sendNEC(0x616A9966, 32);
}


void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);
  irsend.begin();

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", indexpg);
  server.on("/bt1", button1);
  server.on("/bt2", button2);
  server.on("/bt3", button3);
  server.on("/bt4", button4);

  server.begin();
  Serial.println("-----------ETRI REMOTE Server Started--------");
}

void loop() {
  server.handleClient();
}
