#include "ESP8266WiFi.h"
#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#define PIN_BL 2  // LCD Backlight
#define USE_SERIAL Serial
WiFiClient client;
//4x4 Button array
const int numRows = 4;
const int numCols = 4;

//4x4 Button Pin
int pinRows[numRows] = {1, 3, 15, 0 };
int pinCols[numCols] = {2, 9, 10, 16 };

Adafruit_PCD8544 display = Adafruit_PCD8544(14, 13, 12, 5, 4);
ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_BL, OUTPUT);
  digitalWrite(PIN_BL, LOW);

  // Set esp8266 to station mode and disconnect from any AP previously connected to
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // initialize row pins as INPUT_PULLUP
  for (int i = 0; i < numRows; i++) {
    pinMode(pinRows[i], INPUT_PULLUP);
  }


  // initialize column pins as OUTPUT
  for (int j = 0; j < numCols; j++) {
    pinMode(pinCols[j], OUTPUT);
    digitalWrite(pinCols[j], HIGH);    // set initial output as HIGH
  }

  display.begin();
  display.setContrast(40);
  //adjust for your display (if you see a black screen try lowering the value, if all white try increasing it. Max 127)

  display.clearDisplay();
  delay(2000);

  display.clearDisplay();
  display.setTextSize(0);
  display.setTextColor(BLACK);

  display.setCursor(0, 0);
  display.println("ETRI REMOTE");
  display.println("WiFi Scaning..");
  display.display();
  delay(2000);
  display.clearDisplay();

  int networksFound = WiFi.scanNetworks();
  display.setCursor(0, 0);
  display.println("--WiFi INDEX--");
  for (int i = 0; i < networksFound; ++i)
  {
    if (WiFi.SSID(i).substring(0, 4) == "park") {
      display.println(WiFi.SSID(i));
    }
  }

  display.display();
}
void loop() {
  HTTPClient http;


  for (int j = 0; j < numCols; j++) {
    digitalWrite(pinCols[j], LOW);    // set as LOW to check button press
    for (int i = 0; i < numRows; i++) {
      if ( digitalRead(pinRows[i]) == LOW ) {   // check input. LOW is pressed
        Serial.print("Pressed row=");
        Serial.print(i);
        Serial.print(", column=");
        Serial.println(j);


        if (i == 0 && j == 0) {
          WiFi.mode(WIFI_STA);
          WiFi.begin("park_device4", "");;
          display.clearDisplay();
          display.setCursor(0, 0);
          display.println("now connecting device4");
          display.display();
          delay(15000);

          if (WiFi.status() == WL_CONNECTED) {
            display.clearDisplay();             //디스플레이 지우기
            display.setTextSize(1);             //텍스트 사이즈 조절
            display.setTextColor(BLACK);        //텍스트 색
            display.println(WiFi.SSID());
            display.println("1.led");
            display.println("2.led");
            display.println("3.led");
            display.println("4.led");
            display.println("5.allOFF");
            display.display();
            client.println("GET /hello ETRI HTTP/1.1");
            client.println("Host: 192.168.4.1/bt1");
            client.println("User-Agent: ArduinoWiFi/1.1");
            client.println("Connection: close");
            client.println();
          }
          else {
            display.clearDisplay();
            display.println("NOT CONNECTED");
            display.display();
          }
        }


        if (i == 0 && j == 1) {
          WiFi.mode(WIFI_STA);
          WiFi.begin("park_device3", "");

          display.clearDisplay();
          display.setCursor(0, 0);
          display.println("now connecting device3");
          display.display();
          delay(15000);

          if (WiFi.status() == WL_CONNECTED) {
            display.clearDisplay();             //디스플레이 지우기
            display.setTextSize(1);             //텍스트 사이즈 조절
            display.setTextColor(BLACK);        //텍스트 색
            display.println(WiFi.SSID());
            display.println("1.redup");
            display.println("2.reddown");
            display.display();
          }
          else {
            display.clearDisplay();
            display.println("NOT CONNECTED");
            display.display();
          }
        }
        if (i == 0 && j == 2) {
          WiFi.mode(WIFI_STA);
          WiFi.begin("park_device2", "");

          display.clearDisplay();
          display.setCursor(0, 0);
          display.println("now connecting device2");
          display.display();
          delay(15000);

          if (WiFi.status() == WL_CONNECTED) {
            display.clearDisplay();             //디스플레이 지우기
            display.setTextSize(1);             //텍스트 사이즈 조절
            display.setTextColor(BLACK);        //텍스트 색
            display.println(WiFi.SSID());
            display.println("1.Beam Menu");
            display.display();
          }
          else {
            display.clearDisplay();
            display.println("NOT CONNECTED");
            display.display();
          }

        }
        if (i == 0 && j == 3) {
          WiFi.mode(WIFI_STA);
          WiFi.begin("park_device1", "");

          display.clearDisplay();
          display.setCursor(0, 0);
          display.println("now connecting device1");
          display.display();
          delay(15000);

          if (WiFi.status() == WL_CONNECTED) {
            display.clearDisplay();             //디스플레이 지우기
            display.setTextSize(1);             //텍스트 사이즈 조절
            display.setTextColor(BLACK);        //텍스트 색
            display.println(WiFi.SSID());
            display.println("1.Power");
            display.display();
          }
          else {
            display.clearDisplay();
            display.println("NOT CONNECTED");
            display.display();
          }
        }
      }
    }


    digitalWrite(pinCols[j], HIGH);    // set as default (HIGH)
  }
  delay(500);

}
