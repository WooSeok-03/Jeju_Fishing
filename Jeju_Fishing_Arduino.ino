//온습도센서 PIN설정
#include"DHT.h"
#define DHTPIN 3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//블루투스 PIN설정
#include <SoftwareSerial.h>
#define BT_RXD 8
#define BT_TXD 7
SoftwareSerial bluetooth(BT_RXD, BT_TXD);

//비 센서 PIN설정
int RainIn = A1;
int RainDigitalIn = 2;
boolean Raining = false;
int nRaining;


void setup() {
  Serial.begin(9600); //시리얼 모니터 시작
  bluetooth.begin(9600);  //블루투스 시작
  pinMode(2, INPUT);  //비 센서 PIN설정
}

void loop() {
  
  //비 센서
  Raining = !(digitalRead(RainDigitalIn));
  
  if(Raining){
    nRaining = 1; //비가 감지되면 nRaining = 1
  }
  else{
    nRaining = 0; //비가 감지 되지 않으면 nRaining = 0
  }

  //온습도 센서
  int h = dht.readHumidity(); //h 변수에 습도 선언
  int t = dht.readTemperature();  //t 변수에 온도 선언

  //블루투스 - 센서 데이터 전송
  bluetooth.print("{\"temp\":");
  bluetooth.print(t); //온도
  bluetooth.print(",\"hei\":");
  bluetooth.print(h); //습도
  bluetooth.print(",\"isRain\":");
  bluetooth.print(nRaining); //비 오는지 확인
  bluetooth.println("}");

  //시리얼 모니터 출력
  Serial.print("현재 날씨: ");
  Serial.print(nRaining);
  Serial.print("\t");
  Serial.print("현재 온도: ");
  Serial.print(t);
  Serial.print("℃\t");
  Serial.print("현재 습도: ");
  Serial.println(h);
  
}
