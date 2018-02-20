#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <SoftwareSerial.h>
#define SSID "park_device1" //AP ID
#define PASS "123456789" //AP PW
#define DST_IP "192.168.4.1" //AP IP
#define PIN_BL 2  // LCD Backlight

//SCLK, DIN, DC, CE, RST - Nokia 5110 lcd PIN
Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 6, 7);

//4x4 Button array(but only use 3way)
const int numRows = 3;
const int numCols = 3;

//4x4 Button Pin
int pinRows[numRows] = {8, 9, 10};
int pinCols[numCols] = {11, 12, 13};

SoftwareSerial dbgSerial(0, 1); // RX, TX

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Serial.setTimeout(5000);
  dbgSerial.begin(9600); //can't be faster than 19200 for softserial
  dbgSerial.println("ESP8266 Demo");

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
  Serial.println("AT+RST");
  delay(200);

  if (Serial.find("ready"))
  {
    dbgSerial.println("Module is ready");
    Serial.println("Module is ready");
    display.println("ESP is Good");
    display.display();
  }
  else
  {
    dbgSerial.println("Module have no response.");
    Serial.println("Module have no response.");
  }

  //Find WIFI Module NodeMCU & Display
  display.clearDisplay();
  Serial.println("AT+CWLAP");
  delay(200);

  if (Serial.find("park_device1"))
  {
    display.println("1.Device1");
    Serial.println("AT+CWJAP=\"park_device1\",\"123456789\"");
  }
  else {
    display.println("1.Not find D1");
  }

  if (Serial.find("park_device2"))
  {
    display.println("2.Device2");
    Serial.println("AT+CWJAP=\"park_device2\",\"123456789\"");
  }
  else {
    display.println("2.Not find D2");
  }

  display.setTextColor(WHITE, BLACK); // 'inverted' text (배경 까맣게 글자 하얗게)
  display.setTextSize(2);             //텍스트 사이즈 조절
  display.setTextColor(BLACK);        //텍스트 색
  display.display();                  //와이파이 내용 표시

}

void loop()
{

}

