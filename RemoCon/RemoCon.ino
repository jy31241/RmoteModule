#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <SoftwareSerial.h>
#define PIN_BL 2  // LCD Backlight
//SCLK, DIN, DC, CE, RST - Nokia 5110 lcd PIN
Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 6, 7);

//4x4 Button array(but only use 3way)
const int numRows = 3;
const int numCols = 3;

//4x4 Button Pin
int pinRows[numRows] = {8, 9, 10};
int pinCols[numCols] = {11, 12, 13};

SoftwareSerial esp(2, 3);
void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  esp.begin(115200);
  
  //백라이트를 ON 함, HIGH = Turn Backlight OFF, LOW = Turn Backlight ON
  pinMode(PIN_BL, OUTPUT);
  digitalWrite(PIN_BL, LOW);

  //디스플레이 초기화
  display.begin();

  //디스플레이 Contrast 조절 (값이 올라가면 진해짐)
  display.setContrast(60);

  display.clearDisplay();             //디스플레이 지우기
  display.setTextSize(1);             //텍스트 사이즈 조절
  display.setTextColor(BLACK);        //텍스트 색
  display.setCursor(0, 0);            //커서 좌표
  display.println("Loading....");
  display.display();

  //ESP8266 잘 돌아가는지 준비테스트
  String c = "AT+RST";
  Serial.println(c);
  esp.println(c);
  delay(200);

  if (Serial.find("Ready"))
  {
    Serial.println("Module is ready");
    display.println("ESP is Good");
    display.display();
  }
  else
  {
    Serial.println("Module have no response.");
  }

  //Find WIFI Module NodeMCU & Display
  display.clearDisplay();
  Serial.println("AT+CWLAP");
  delay(100);

  if (Serial.find("ERROR")) {
    setup();
  }
  else {
    delay(200);

    if (Serial.find("park_device1"))
    {
      display.println("1.Device1");
    }
    else {
      display.println("1.Not find D1");
    }

    if (Serial.find("park_device2"))
    {
      display.println("2.Device2");
    }
    else {
      display.println("2.Not find D2");
    }

    display.setTextColor(WHITE, BLACK); // 'inverted' text (배경 까맣게 글자 하얗게)
    display.setTextSize(2);             //텍스트 사이즈 조절
    display.setTextColor(BLACK);        //텍스트 색
    display.display();                  //와이파이 내용 표시
  }

  // initialize row pins as INPUT_PULLUP
  for (int i = 0; i < numRows; i++) {
    pinMode(pinRows[i], INPUT_PULLUP);
  }

  // initialize column pins as OUTPUT
  for (int j = 0; j < numCols; j++) {
    pinMode(pinCols[j], OUTPUT);
    digitalWrite(pinCols[j], HIGH);    // set initial output as HIGH
  }
}


void loop()
{
  // Check input
  for (int j = 0; j < numCols; j++) {
    digitalWrite(pinCols[j], LOW);    // set as LOW to check button press
    for (int i = 0; i < numRows; i++) {
      if ( digitalRead(pinRows[i]) == LOW ) {   // check input. LOW is pressed
        Serial.print("Pressed row=");
        Serial.print(i);
        Serial.print(", column=");
        Serial.println(j);
        if (i == 0 && j == 0) {
          Serial.println("AT+CWJAP=\"park_device1\",\"123456789\""); // 0,0좌표 버튼 누르면 device1 연결
          if (Serial.find("OK")) {
            display.clearDisplay();             //디스플레이 지우기
            display.setTextSize(1);             //텍스트 사이즈 조절
            display.setTextColor(BLACK);        //텍스트 색
            display.println("--Device1--");
            display.println("1.ON");
            display.println("2.OFF");
            display.println("3.Back");
            display.display();
          }
        }

        else if (i == 0 && j == 1) {
          Serial.println("AT+CWJAP=\"park_device2\",\"123456789\"");
          if (Serial.find("OK")) {
            display.clearDisplay();             //디스플레이 지우기
            display.setTextSize(1);             //텍스트 사이즈 조절
            display.setTextColor(BLACK);        //텍스트 색
            display.println("--Device2--");
            display.println("1.ON");
            display.println("2.OFF");
            display.println("3.Back");
            display.display();
          }
        }
      }
    }
    digitalWrite(pinCols[j], HIGH);    // set as default (HIGH)
  }
  delay(500);
}


