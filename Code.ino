#define REMOTEXY_MODE__ESP8266WIFI_LIB_POINT
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RemoteXY.h>

#define REMOTEXY_WIFI_SSID "*********"
#define REMOTEXY_WIFI_PASSWORD "*********"
#define REMOTEXY_SERVER_PORT 6377

LiquidCrystal_I2C lcd(0x27, 16, 2) ;

#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,29,0,0,0,93,0,10,25,0,
  1,0,43,24,16,16,2,31,88,0,
  1,0,81,25,16,16,2,31,88,0,
  1,0,63,6,16,16,2,31,89,0,
  1,0,63,43,16,16,2,31,89,0,
  7,36,5,4,43,5,2,26,133,11,
  7,36,5,10,43,5,2,26,133,11,
  1,2,65,27,12,12,37,31,72,0,
  1,2,10,42,12,12,52,31,76,0,
  1,1,5,16,18,5,15,31,67,0 };

struct {

  uint8_t Left; 
  uint8_t Right;  
  uint8_t Front; 
  uint8_t Back;  
  char edit_1[17];  
  char edit_2[17];   
  uint8_t horn; 
  uint8_t led;  
  uint8_t clear; 
 
  uint8_t connect_flag; 

} RemoteXY;
#pragma pack(pop)


void setup() 
{
  RemoteXY_Init (); 

  //initial state
  digitalWrite(D0, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  digitalWrite(D8, LOW);
  
  lcd.init();
  lcd.backlight();
  setCursor(5,0);
  lcd.print("Started");
  delay(1000);
  lcd.clear();
  
  pinMode(D5,OUTPUT);//IN1
  pinMode(D6,OUTPUT);//IN2
  pinMode(D7,OUTPUT);//IN3
  pinMode(D8,OUTPUT);//IN4
  pinMode(D0,OUTPUT);//BUZZER 
  pinMode(D3,OUTPUT);//LED  
}

void loop() 
{ 
  RemoteXY_Handler ();
  if(RemoteXY.Front != 0){
    digitalWrite(D7, HIGH);
    digitalWrite(D6, HIGH);
  }
  else if(RemoteXY.Right != 0){
     digitalWrite(D7, HIGH);
     digitalWrite(D5, HIGH);
  }
  else if(RemoteXY.Back != 0){
    digitalWrite(D5, HIGH);
    digitalWrite(D8, HIGH);
  }
  else if(RemoteXY.Left != 0){
    digitalWrite(D8, HIGH);
    digitalWrite(D6, HIGH);
  }
  else if(RemoteXY.led != 0){
    digitalWrite(D3, HIGH);
  }
  else if(RemoteXY.horn != 0){
    digitalWrite(D0, HIGH);
  }
  else if(RemoteXY.clear != 0){
    lcd.clear();
  }
  else{
    digitalWrite(D0, LOW);
    digitalWrite(D3, LOW);
    digitalWrite(D5, LOW);
    digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);
    digitalWrite(D8, LOW);
  }
  setCursor(0, 0);
  lcd.print(edit_1);
  setCursor(0, 1);
  lcd.print(edit_2);
}
