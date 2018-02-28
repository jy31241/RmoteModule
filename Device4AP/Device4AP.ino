#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <RGBLED.h>

const char* ssid = "park_device4";
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
  "<h1>ETRI 4lamp</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<div>"
  "<P>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt1'\" value=\"light1\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt2'\" value=\"light2\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt3'\" value=\"light3\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt4'\" value=\"light4\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt5'\" value=\"OFF\"></INPUT>"
  "</P>"
  "</div>"
  "</FORM>"
  "</body>"
  "</html>";

const char light1[] =
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
  "<h1>1</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<div>"
  "<P>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt1'\" value=\"light1\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt2'\" value=\"light2\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt3'\" value=\"light3\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt4'\" value=\"light4\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt5'\" value=\"OFF\"></INPUT>"
  "</P>"
  "</div>"
  "</FORM>"
  "</body>"
  "</html>";


const char light2[] =
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
  "<h1>2</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<div>"
  "<P>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt1'\" value=\"light1\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt2'\" value=\"light2\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt3'\" value=\"light3\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt4'\" value=\"light4\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt5'\" value=\"OFF\"></INPUT>"
  "</P>"
  "</div>"
  "</FORM>"
  "</body>"
  "</html>";

const char light3[] =
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
  "<h1>3</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<div>"
  "<P>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt1'\" value=\"light1\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt2'\" value=\"light2\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt3'\" value=\"light3\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt4'\" value=\"light4\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt5'\" value=\"OFF\"></INPUT>"
  "</P>"
  "</div>"
  "</FORM>"
  "</body>"
  "</html>";

const char light4[] =
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
  "<h1>4</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<div>"
  "<P>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt1'\" value=\"light1\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt2'\" value=\"light2\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt3'\" value=\"light3\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt4'\" value=\"light4\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt5'\" value=\"OFF\"></INPUT>"
  "</P>"
  "</div>"
  "</FORM>"
  "</body>"
  "</html>";

const char alloff[] =
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
  "<h1>OFF</h1>"
  "<FORM action=\"/\" method=\"post\">"
  "<div>"
  "<P>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt1'\" value=\"light1\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt2'\" value=\"light2\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt3'\" value=\"light3\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt4'\" value=\"light4\"></INPUT>"
  "<INPUT style=\"background:#1AAB8A; color:#fff;  border:none;  position:relative;  height:30px;  font-size:1.6em;  padding:0 2em; cursor:pointer;  transition:800ms ease all;  outline:none;border-width:2px;border-style:solid;\" type=\"button\" class=\"button\" onclick=\"location.href='/bt5'\" value=\"OFF\"></INPUT>"
  "</P>"
  "</div>"
  "</FORM>"
  "</body>"
  "</html>";



ESP8266WebServer server(80); //port 80
int R = 1;
int G = 1;
int B = 1;

void indexpg() {
  server.send(200, "text/html", indexsource);
}

void button1() {
  server.send(200, "text/html", light1);
  digitalWrite(2, HIGH);
}

void button2() {
  server.send(200, "text/html", light2);
  digitalWrite(0, HIGH);
}

void button3() {
  server.send(200, "text/html", light3);
  digitalWrite(4, HIGH);
}

void button4() {
  server.send(200, "text/html", light4);
  digitalWrite(5, HIGH);
}

void button5() {
  server.send(200, "text/html", alloff);
  digitalWrite(2, LOW);
  digitalWrite(0, LOW);
  digitalWrite(4, LOW);    
  digitalWrite(5, LOW);
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  pinMode(2, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

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
  server.begin();
  Serial.println("-----------ETRI REMOTE Server Started--------");
}


void loop() {
  server.handleClient();
}
