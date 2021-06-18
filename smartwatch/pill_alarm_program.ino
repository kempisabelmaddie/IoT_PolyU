#include <M5StickC.h>
#include <SPI.h>
#include <Blynk.h> 
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#define BLYNK_PRINT Serial
#define REDLED 10

#include "TRIGGER_WIFI.h"               /*Includes ESP8266WiFi.h and WiFiClientSecure.h, just have these two libraries downloaded before*/
#include "TRIGGER_GOOGLESHEETS.h"

char auth[] = "dYe_r3bdakfCGBalxSdnPFxfboXzGu9j";
char ssid[] = "IoT-Lib";
char pass[] = "libiot6909";

/**********Google Sheets Definations***********/
char column_name_in_sheets[ ][20] = {"Pill"};                        /*1. The Total no of column depends on how many value you have created in Script of Sheets;2. It has to be in order as per the rows decided in google sheets*/
String Sheets_GAS_ID = "AKfycbyOOMP8VcgVrrRysD15X9VXqPc4oIGtclrZgqUnCQysDG3QCEtOuKIEXKU8UEdknw-FAw";                                         /*This is the Sheets GAS ID, you need to look for your sheets id*/
int No_of_Parameters = 1;                                                                /*Here No_of_Parameters decides how many parameters you want to send it to Google Sheets at once, change it according to your needs*/
/*********************************************/

String weekdays[7]={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};

RTC_TimeTypeDef RTC_TimeStruct;
RTC_DateTypeDef RTC_DateStruct;

int displayer = 0;
int cholesterol_taken = 0;
int bloodpres_taken = 0;
int pinValue = 0;

BLYNK_WRITE(V0)
{
  pinValue = param.asInt();
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("Time: %02d : %02d : %02d\n",RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds);
  M5.Lcd.println("Medication Reminder:");
  switch (pinValue) {
    case 1:
      M5.Lcd.println("Take 1 cholestorol pill");
      break;
    case 2:
      M5.Lcd.println("Take 1 blood pressure pill");
      break;
    default:
      // statements
      break;
  }
  M5.Lcd.println("\nPress button after pill");
  digitalWrite(REDLED, LOW);
  displayer = 1;
  delay(5000);
}

void setup() {
  // put your setup code here, to run once:

  while (!Serial);

  WIFI_Connect(ssid,pass);                                                     /*Provide you Wi-Fi SSID and password to connect to Wi-Fi*/
  Google_Sheets_Init(column_name_in_sheets, Sheets_GAS_ID, No_of_Parameters );         /*Sets the column name for Google Sheets, the GAS ID, and the No of Parameter we want to send*/
  
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(40, 0, 2);
  RTC_TimeTypeDef TimeStruct;
  TimeStruct.Hours   = 18;
  TimeStruct.Minutes = 29;
  TimeStruct.Seconds = 0;
  M5.Rtc.SetTime(&TimeStruct);
  RTC_DateTypeDef DateStruct;
  DateStruct.WeekDay = 0;
  DateStruct.Month = 5;
  DateStruct.Date = 24;
  DateStruct.Year = 2021;
  M5.Rtc.SetData(&DateStruct);
  
  pinMode(REDLED, OUTPUT);
  digitalWrite(REDLED, HIGH);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  M5.update();
  Blynk.run();
  String currentTime = "\xF0\x9F\x95\x92" + String(RTC_TimeStruct.Hours) + ":" + String(RTC_TimeStruct.Minutes) + ":" + String(RTC_TimeStruct.Seconds);
  String currentDate = "\xF0\x9F\x93\x85" + String(RTC_DateStruct.Date) + "/" + String(RTC_DateStruct.Month)+ "/" +String(RTC_DateStruct.Year);
  Blynk.virtualWrite(V1, currentTime);                                          
  Blynk.virtualWrite(V2, currentDate); 
  
  if (displayer == 0){
    M5.Rtc.GetTime(&RTC_TimeStruct);
    M5.Rtc.GetData(&RTC_DateStruct);
    M5.Lcd.setCursor(0, 15);
    M5.Lcd.printf("Date: %04d-%02d-%02d\n",RTC_DateStruct.Year, RTC_DateStruct.Month,RTC_DateStruct.Date);
    M5.Lcd.printf("Weekday: %s\n",weekdays[RTC_DateStruct.WeekDay]);
    M5.Lcd.printf("Time: %02d : %02d : %02d\n",RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds);
    delay(500);
  }
  else{
    if (M5.BtnA.wasReleased()){
      M5.Lcd.fillScreen(TFT_BLACK);
      M5.Lcd.setCursor(0, 0);
      digitalWrite(REDLED, HIGH);
      String pillName = "";
      switch (pinValue) {
        case 1:
          cholesterol_taken = cholesterol_taken + 1;
          Blynk.virtualWrite(V3, cholesterol_taken);
          Serial.print("cholesterol pill taken: ");
          Serial.println(cholesterol_taken);
          pillName = "cholesterol";
          Serial.println(pillName);
          break;
        case 2:
          bloodpres_taken = bloodpres_taken + 1;
          Blynk.virtualWrite(V4, bloodpres_taken);
          Serial.print("blood pressure pill taken: ");
          Serial.println(bloodpres_taken);
          pillName = "blood";
          Serial.println(pillName);
          break;
        default:
          // statements
          break;
      }
      displayer = 0;
      Data_to_Sheets(No_of_Parameters,  pillName);         /*1. This function accepts multiple float parameter, here No_of_Parameters decides how many parameters you want to send to Google Sheets; 2. The values sent should be in order as per the column in Google Sheets*/
      delay(3000);
    }
  }
}
