#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

const char *ssid = "JYPNODEMCU";
const char *password = "123456789";
const char htmlsource[] =
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
"<h1>ETRI REMOTE SERVER !!!!!!!!</h1>"
"<FORM action=\"/\" method=\"post\">"
"<P>"
"<INPUT type=\"button\" name=\"tv\" value=\"1\">TV REMOTE<BR>"
"<INPUT type=\"button\" name=\"air\" value=\"0\">AIRCON REMOTE<BR>"
"</P>"
"</FORM>"
"</body>"
"</html>";
ESP8266WebServer server(80);

void handleRoot() {
  server.send(200,"text/html", htmlsource);
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
	server.on("/", handleRoot);
	server.begin();
	Serial.println("HTTP server started");
}

void loop() {
	server.handleClient();
}
