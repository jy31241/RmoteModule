#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
IRsend irsend(4); // An IR LED is controlled by GPIO pin 4 (D2)

const char* ssid = "park_device2";
const char* password = "123456789";
const char indexsource[] =
  "<!DOCTYPE HTML>"
  "<html>"
  "<head>"
  "<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
  "<titleETRI Beam projector</title>"
  "<style>"
  "\"body { background-color: #808080; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }\""
  "</style>"
  "</head>"
  "<body>"
  "<h1>ETRI BEAM PROJECTER</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<div>"
  "<P>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt1'\" value=\"menu\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt2'\" value=\"up\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt3'\" value=\"down\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\"type=\"button\" class=\"button\" onclick=\"location.href='/bt4'\" value=\"left\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\"type=\"button\" class=\"button\" onclick=\"location.href='/bt5'\" value=\"right\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt6'\" value=\"enter\"></INPUT>"
  "</P>"
  "</div>"
  "</FORM>"
  "</body>"
  "</html>";

const char menu[] =
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
  "<h1>Beam Menu</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<div>"
  "<P>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt1'\" value=\"menu\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt2'\" value=\"up\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt3'\" value=\"down\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\"type=\"button\" class=\"button\" onclick=\"location.href='/bt4'\" value=\"left\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\"type=\"button\" class=\"button\" onclick=\"location.href='/bt5'\" value=\"right\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt6'\" value=\"enter\"></INPUT>"
  "</P>"
  "</div>"
  "</FORM>"
  "</body>"
  "</html>";


const char up[] =
  "<!DOCTYPE HTML>"
  "<html>"
  "<head>"
  "<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
  "<titleETRI REMOTE SERVER</title>"
  "<style>"
  "\"body { background-color: #808080; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }\""
  "INPUT{background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:60px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;}"
  "</style>"
  "</head>"
  "<body>"
  "<h1>Beam UP</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<div>"
   "<P>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt1'\" value=\"menu\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt2'\" value=\"up\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt3'\" value=\"down\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\"type=\"button\" class=\"button\" onclick=\"location.href='/bt4'\" value=\"left\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\"type=\"button\" class=\"button\" onclick=\"location.href='/bt5'\" value=\"right\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt6'\" value=\"enter\"></INPUT>"
  "</P>"
  "</div>"
  "</FORM>"
  "</body>"
  "</html>";

const char down[] =
  "<!DOCTYPE HTML>"
  "<html>"
  "<head>"
  "<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
  "<titleETRI REMOTE SERVER</title>"
  "<style>"
  "\"body { background-color: #808080; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }\""
  "INPUT{background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:60px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;}"
  "</style>"
  "</head>"
  "<body>"
  "<h1>Beam Down</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<div>"
  "<P>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt1'\" value=\"menu\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt2'\" value=\"up\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt3'\" value=\"down\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\"type=\"button\" class=\"button\" onclick=\"location.href='/bt4'\" value=\"left\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\"type=\"button\" class=\"button\" onclick=\"location.href='/bt5'\" value=\"right\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt6'\" value=\"enter\"></INPUT>"
  "</P>"
  "</div>"
  "</FORM>"
  "</body>"
  "</html>";

const char left[] =
  "<!DOCTYPE HTML>"
  "<html>"
  "<head>"
  "<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
  "<titleETRI REMOTE SERVER</title>"
  "<style>"
  "\"body { background-color: #808080; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }\""
  "INPUT{background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:60px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;}"
  "</style>"
  "</head>"
  "<body>"
  "<h1>Beam left</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<div>"
  "<P>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt1'\" value=\"menu\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt2'\" value=\"up\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt3'\" value=\"down\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\"type=\"button\" class=\"button\" onclick=\"location.href='/bt4'\" value=\"left\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\"type=\"button\" class=\"button\" onclick=\"location.href='/bt5'\" value=\"right\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt6'\" value=\"enter\"></INPUT>"
  "</P>"
  "</div>"
  "</FORM>"
  "</body>"
  "</html>";

const char right[] =
  "<!DOCTYPE HTML>"
  "<html>"
  "<head>"
  "<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
  "<titleETRI REMOTE SERVER</title>"
  "<style>"
  "\"body { background-color: #808080; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }\""
  "INPUT{background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:60px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;}"
  "</style>"
  "</head>"
  "<body>"
  "<h1>Beam Right</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<div>"
  "<P>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt1'\" value=\"menu\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt2'\" value=\"up\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt3'\" value=\"down\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\"type=\"button\" class=\"button\" onclick=\"location.href='/bt4'\" value=\"left\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\"type=\"button\" class=\"button\" onclick=\"location.href='/bt5'\" value=\"right\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt6'\" value=\"enter\"></INPUT>"
  "</P>"
  "</div>"
  "</FORM>"
  "</body>"
  "</html>";

const char enter[] =
  "<!DOCTYPE HTML>"
  "<html>"
  "<head>"
  "<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
  "<titleETRI REMOTE SERVER</title>"
  "<style>"
  "\"body { background-color: #808080; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }\""
  "INPUT{background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:60px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;}"
  "</style>"
  "</head>"
  "<body>"
  "<h1>Beam enter</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<div>"
  "<P>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt1'\" value=\"menu\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt2'\" value=\"up\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt3'\" value=\"down\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\"type=\"button\" class=\"button\" onclick=\"location.href='/bt4'\" value=\"left\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\"type=\"button\" class=\"button\" onclick=\"location.href='/bt5'\" value=\"right\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt6'\" value=\"enter\"></INPUT>"
  "</P>"
  "</div>"
  "</FORM>"
  "</body>"
  "</html>";


ESP8266WebServer server(80); //port 80

void indexpg() {
  server.send(200, "text/html", indexsource);
}

void button1() {
  server.send(200, "text/html", menu);
  irsend.sendNEC(0x1897629D, 32);
}

void button2() {
  server.send(200, "text/html", up);
  irsend.sendNEC(0x18971DE2, 32);
}

void button3() {
  server.send(200, "text/html", down);
  irsend.sendNEC(0x18973DC2, 32);
}

void button4() {
  server.send(200, "text/html", left);
  irsend.sendNEC(0x18977D82, 32);
}

void button5() {
  server.send(200, "text/html", right);
  irsend.sendNEC(0x18975DA2, 32);
}

void button6() {
  server.send(200, "text/html", enter);
  irsend.sendNEC(0x1897E817, 32);
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
  server.on("/bt5", button5);
  server.on("/bt6", button6);

  server.begin();
  Serial.println("-----------ETRI REMOTE Server Started--------");
}

void loop() {
  server.handleClient();
}
