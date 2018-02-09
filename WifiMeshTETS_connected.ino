#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;
const char* ssid   = "Mesh_Node530825";
void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid);

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
