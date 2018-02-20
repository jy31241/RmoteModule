C#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#define PIN_BL 2   //백라이트 제어를 위한 핀연결
 
//SCLK, DIN, DC, CE, RST 핀연결
Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 6, 7);

//4x4 버튼 핀 연결
const int numRows= 3;
const int numCols= 3;
 
int pinRows[numRows] = {8,9,10};
int pinCols[numCols] = {11,12,13};

void setup()
{
  Serial.begin(9600);
  //백라이트를 ON 함, HIGH = Turn Backlight OFF, LOW = Turn Backlight ON
  pinMode(PIN_BL,OUTPUT); 
  digitalWrite(PIN_BL,LOW); 

  //디스플레이 초기화
  display.begin();
 
  //디스플레이 Contrast 조절 (값이 올라가면 진해짐)
  display.setContrast(60);
 
  //텍스트 디스플레이
  display.clearDisplay();             //디스플레이 지우기
  display.setTextSize(1);             //텍스트 사이즈 조절
  display.setTextColor(BLACK);        //텍스트 색
  display.setCursor(0,0);             //커서 좌표
  display.println("1.Lamp"); 
  display.println("2.RGB Lamp ");
  display.println("3.Screen");
  display.println("4.TV");
  display.println("5.AirCon");
  display.setTextColor(WHITE, BLACK); // 'inverted' text (배경 까맣게 글자 하얗게)
  display.setTextSize(2);             //텍스트 사이즈 조절
  display.setTextColor(BLACK);        //텍스트 색
  display.display();                  //위의 설정내용 표시

   for(int i=0; i<numRows; i++) {
        pinMode(pinRows[i], INPUT_PULLUP);
    }
    for(int j=0; j<numCols; j++) {
        pinMode(pinCols[j], OUTPUT);
        digitalWrite(pinCols[j], HIGH);    // set initial output as HIGH
    }
}
void loop() {
    // Check input
    for(int j=0; j<numCols; j++) {
        digitalWrite(pinCols[j], LOW);    // set as LOW to check button press
        for(int i=0; i<numRows; i++) {
            if( digitalRead(pinRows[i]) == LOW ) {    // check input. LOW is pressed
                Serial.print("Pressed row=");
                Serial.print(i);
                Serial.print(", column=");
                Serial.println(j);
                if(i==0 && j==0){
                    display.clearDisplay();             //디스플레이 지우기
                    display.setTextSize(1);             //텍스트 사이즈 조절
                    display.setTextColor(BLACK);        //텍스트 색
                    display.println("--Lamp Mode--");
                    display.println("1.ON");
                    display.println("2.OFF");
                    display.println("3.Back");
                    display.display();
         
                }

                    else if(i==0 && j==1){
                    display.clearDisplay();             //디스플레이 지우기
                    display.setTextSize(1);             //텍스트 사이즈 조절
                    display.setTextColor(BLACK);        //텍스트 색
                    display.println("--RGB Mode--");
                    display.println("1.ON");
                    display.println("2.OFF");
                    display.println("3.Back");
                    display.display();
                    }

                    else if(i==0 && j==2){
                    display.clearDisplay();             //디스플레이 지우기
                    display.setTextSize(1);             //텍스트 사이즈 조절
                    display.setTextColor(BLACK);        //텍스트 색
                    display.println("--Scr Mode--");
                    display.println("1.ON");
                    display.println("2.OFF");
                    display.println("3.Back");
                    display.display();
                    }
                    
                    else if(i==1 && j==0){
                    display.clearDisplay();             //디스플레이 지우기
                    display.setTextSize(1);             //텍스트 사이즈 조절
                    display.setTextColor(BLACK);        //텍스트 색
                    display.println("--TV Mode--");
                    display.println("1.ON");
                    display.println("2.OFF");
                    display.println("3.Back");
                    display.display();
                    }

                    else if(i==1 && j==1){
                    display.clearDisplay();             //디스플레이 지우기
                    display.setTextSize(1);             //텍스트 사이즈 조절
                    display.setTextColor(BLACK);        //텍스트 색
                    display.println("--Air Mode--");
                    display.println("1.ON");
                    display.println("2.OFF");
                    display.println("3.Back");
                    display.display();
                    }
                }
        }
        digitalWrite(pinCols[j], HIGH);    // set as default (HIGH)
    }
    delay(500);
}


