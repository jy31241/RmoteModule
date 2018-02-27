#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <RGBLED.h>

RGBLED rgbLed(1, 3, 15, COMMON_ANODE);

const char* ssid = "park_device3";
const char* password = "123456789";
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
  "<h1>ETRI RGB</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<div>"
  "<P>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt1'\" value=\"RUP\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt2'\" value=\"RDOWN\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt3'\" value=\"GUP\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt4'\" value=\"GDOWN\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt5'\" value=\"BUP\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt6'\" value=\"BDOWN\"></INPUT>"
  "</P>"
  "</div>"
  "</FORM>"
  "</body>"
  "</html>";

const char rup[] =
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
  "<h1>Red UP</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<div>"
  "<P>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt1'\" value=\"RUP\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt2'\" value=\"RDOWN\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt3'\" value=\"GUP\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt4'\" value=\"GDOWN\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt5'\" value=\"BUP\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt6'\" value=\"BDOWN\"></INPUT>"
  "</P>"
  "</div>"
  "</FORM>"
  "</body>"
  "</html>";


const char rdown[] =
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
  "<h1>Red Down</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<div>"
  "<P>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt1'\" value=\"RUP\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt2'\" value=\"RDOWN\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt3'\" value=\"GUP\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt4'\" value=\"GDOWN\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt5'\" value=\"BUP\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt6'\" value=\"BDOWN\"></INPUT>"
  "</P>"
  "</div>"
  "</FORM>"
  "</body>"
  "</html>";

const char gup[] =
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
  "<h1>Green UP</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<div>"
  "<P>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt1'\" value=\"RUP\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt2'\" value=\"RDOWN\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt3'\" value=\"GUP\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt4'\" value=\"GDOWN\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt5'\" value=\"BUP\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt6'\" value=\"BDOWN\"></INPUT>"
  "</P>"
  "</div>"
  "</FORM>"
  "</body>"
  "</html>";

const char gdown[] =
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
  "<h1>Green Down</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<div>"
  "<P>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt1'\" value=\"RUP\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt2'\" value=\"RDOWN\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt3'\" value=\"GUP\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt4'\" value=\"GDOWN\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt5'\" value=\"BUP\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt6'\" value=\"BDOWN\"></INPUT>"
  "</P>"
  "</div>"
  "</FORM>"
  "</body>"
  "</html>";

const char bup[] =
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
  "<h1>Blue Up</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<div>"
  "<P>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt1'\" value=\"RUP\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt2'\" value=\"RDOWN\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt3'\" value=\"GUP\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt4'\" value=\"GDOWN\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt5'\" value=\"BUP\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt6'\" value=\"BDOWN\"></INPUT>"
  "</P>"
  "</div>"
  "</FORM>"
  "</body>"
  "</html>";

const char bdown[] =
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
  "<h1>Blue Down</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<div>"
  "<P>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt1'\" value=\"RUP\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt2'\" value=\"RDOWN\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt3'\" value=\"GUP\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt4'\" value=\"GDOWN\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt5'\" value=\"BUP\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt6'\" value=\"BDOWN\"></INPUT>"
  "</P>"
  "</div>"
  "</FORM>"
  "</body>"
  "</html>";

ESP8266WebServer server(80); //port 80
int R = 0;
int G = 0;
int B = 0;

rgbLed.writeRGB(R, G, B);

void indexpg() {
  server.send(200, "text/html", indexsource);
}

void button1() {
  server.send(200, "text/html", rup);
  R += 32;
  rgbLed.writeRGB(R, G, B);
}

void button2() {
  server.send(200, "text/html", rdown);
  R -= 32;
  rgbLed.writeRGB(R, G, B);
}

void button3() {
  server.send(200, "text/html", gup);
  G += 32;
  rgbLed.writeRGB(R, G, B);
}

void button4() {
  server.send(200, "text/html", gdown);
  G -= 32;
  rgbLed.writeRGB(R, G, B);
}

void button5() {
  server.send(200, "text/html", bup);
  B += 32;
  rgbLed.writeRGB(R, G, B);
}

void button6() {
  server.send(200, "text/html", bdown);
  B -= 32;
  rgbLed.writeRGB(R, G, B);
}


void setup() {
  Serial.begin(115200);
  Serial.println();
  String ledType = (rgbLed.commonType == 0) ? "COMMON_CATHODE" : "COMMON_ANODE";

  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", indexpg);
  server.on("/bt1", button1);
  server.on("/bt2", button2);
  server.on("/bt3", button3);
  server.on("/bt4", button4);
  server.on("/bt5", button5);
  server.on("/bt6", button6);
  server.begin();
  Serial.println("-----------ETRI REMOTE Server Started--------");
}

void loop() {
  server.handleClient();
}
