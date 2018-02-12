#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <SoftwareSerial.h>
#define DEBUG true
SoftwareSerial esp8266(2,3);

ESP8266WiFiMulti wifiMulti;
const char* ssid   = "JYPHONE";
const char* pw   = "123456789";
void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid,pw);

  Serial.begin(9600);
  esp8266.begin(9600);

  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  sendData("AT+CWMODE=2\r\n",1000,DEBUG); // configure as access point
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80 

}
void loop() {
    if(WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi not connected!");
        delay(1000);
    }
    else{
      Serial.println("WIFI SUCCESs");
      Serial.println(WiFi.SSID()); 
      Serial.println(WiFi.localIP());
      delay(1000);
    }
    
}
