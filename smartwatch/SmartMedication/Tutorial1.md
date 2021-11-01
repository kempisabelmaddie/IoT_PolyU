[< Back: Tutorial 0 - Arduino Setup](https://github.com/kempisabelmaddie/IoT_PolyU/blob/main/smartwatch/SmartMedication/Tutorial0.md)\
[> Next: Tutorial 2 - Alarm Setup](https://github.com/kempisabelmaddie/IoT_PolyU/blob/main/smartwatch/SmartMedication/Tutorial2.md)
# Tutorial 1 - Clock Display
A smartwatch must have a time/clock display. The clock display can be easily done by using the given code from M5Stick C Arduino examples.

## 1) NTP Clock
NTP stands for Network Time Protocol, it is a protocol that allows the synchronization of system clocks (from desktops to servers).

With reference to the 2 links below, a clock can be displayed on the smartwatch:\
https://www.hackster.io/herbert-stiebritz/very-simple-m5stickc-clock-08275b \
https://github.com/tanakamasayuki/M5StickC-examples/blob/master/Update/M5StickC-Update-NTP/M5StickC-Update-NTP.ino


Copy and paste the code below to your Arduino program.

```arduino
#include <M5StickC.h>
#include <WiFi.h>
#include "time.h"
#include <Update.h>

WiFiClient client;

const char* ntpServer     = "ntp.jst.mfeed.ad.jp";
const int time_difference = 8 * 3600; // HONG KONG

bool ntp_setup = false;
RTC_TimeTypeDef RTC_TimeStruct;
RTC_DateTypeDef RTC_DateStruct;

void execOTA(String host, int port, String bin);

void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE,BLACK);

  Wire1.beginTransmission(0x51);
  Wire1.write(0x00);
  Wire1.write(0x00);
  Wire1.write(0x00);
  Wire1.endTransmission();
  Serial.println("RTC status reset");

  // connect to WiFi
  Serial.printf("Connecting");
  WiFi.begin();

  // Set ntp time to local
  configTime(time_difference, 0, ntpServer);
}

void loop() {
  M5.update();
  M5.Lcd.setCursor(0, 8 * 2);

  // RTC NTP set
  struct tm timeInfo;
  if (!ntp_setup && WiFi.status() == WL_CONNECTED && getLocalTime(&timeInfo)) {
    ntp_setup = true;

    // Set RTC time
    RTC_TimeTypeDef TimeStruct;
    TimeStruct.Hours   = timeInfo.tm_hour;
    TimeStruct.Minutes = timeInfo.tm_min;
    TimeStruct.Seconds = timeInfo.tm_sec;
    M5.Rtc.SetTime(&TimeStruct);

    RTC_DateTypeDef DateStruct;
    DateStruct.WeekDay = timeInfo.tm_wday;
    DateStruct.Month = timeInfo.tm_mon + 1;
    DateStruct.Date = timeInfo.tm_mday;
    DateStruct.Year = timeInfo.tm_year + 1900;
    M5.Rtc.SetData(&DateStruct);
  }

  float vbat = M5.Axp.GetBatVoltage();
  int vlevel = ( vbat - 3.2 ) / 0.8 * 100;
  if ( vlevel < 0 ) {
    vlevel = 0;
  }
  if ( 100 < vlevel ) {
    vlevel = 100;
  }
  M5.Lcd.println();

  // RTC
  static const char *wd[7] = {"Sun", "Mon", "Tue", "Wed", "Thr", "Fri", "Sat"};
  M5.Rtc.GetTime(&RTC_TimeStruct);
  M5.Rtc.GetData(&RTC_DateStruct);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(40, 5, 2);
  M5.Lcd.println("Simple Clock");
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(27, 20);
  M5.Lcd.printf("%02d:%02d:%02d\n", RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds);
  M5.Lcd.setCursor(27, 55);
  M5.Lcd.setTextSize(1);
  M5.Lcd.printf("%04d-%02d-%02d(%s)\n", RTC_DateStruct.Year, RTC_DateStruct.Month, RTC_DateStruct.Date, wd[RTC_DateStruct.WeekDay]);

  M5.Lcd.println();
  delay(100);
}

// Utility to extract header value from headers
String getHeaderValue(String header, String headerName) {
  return header.substring(strlen(headerName.c_str()));
}

// OTA Logic
void execOTA(String host, int port, String bin) {
  Serial.println("Connecting to Wi-fi");

  // Connect to provided SSID and PSWD
  WiFi.begin();

  // Wait for connection to establish
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("."); // Keep the serial monitor lit!
    delay(500);
  }

  // Connection Succeed
  Serial.println("");
  Serial.println("Connected to Wi-Fi");

  long contentLength = 0;
  bool isValidContentType = false;

  Serial.println("Connecting to: " + String(host));
  if (client.connect(host.c_str(), port)) {
    Serial.println("Fetching Bin: " + String(bin));

    client.print(String("GET ") + bin + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Cache-Control: no-cache\r\n" +
                 "Connection: close\r\n\r\n");

    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println("Client Timeout !");
        client.stop();
        return;
      }
    }

    while (client.available()) {
      String line = client.readStringUntil('\n');
      line.trim();

      if (!line.length()) {
        break;
      }

      if (line.startsWith("HTTP/1.1")) {
        if (line.indexOf("200") < 0) {
          Serial.println("Got a non 200 status code from server. Exiting OTA Update.");
          break;
        }
      }

      if (line.startsWith("Content-Length: ")) {
        contentLength = atol((getHeaderValue(line, "Content-Length: ")).c_str());
        Serial.println("Got " + String(contentLength) + " bytes from server");
      }

      if (line.startsWith("Content-Type: ")) {
        String contentType = getHeaderValue(line, "Content-Type: ");
        Serial.println("Got " + contentType + " payload.");
        if (contentType == "application/octet-stream") {
          isValidContentType = true;
        }
      }
    }
  } else {
    Serial.println("Connection to " + String(host) + " failed. Please check your setup");
  }

  Serial.println("contentLength : " + String(contentLength) + ", isValidContentType : " + String(isValidContentType));

  if (contentLength && isValidContentType) {
    bool canBegin = Update.begin(contentLength);

    if (canBegin) {
      Serial.println("Begin OTA. This may take 2 - 5 mins to complete. Things might be quite for a while.. Patience!");
      size_t written = Update.writeStream(client);

      if (written == contentLength) {
        Serial.println("Written : " + String(written) + " successfully");
      } else {
        Serial.println("Written only : " + String(written) + "/" + String(contentLength) + ". Retry?" );
      }

      if (Update.end()) {
        Serial.println("OTA done!");
        if (Update.isFinished()) {
          Serial.println("Update successfully completed. Rebooting.");
          ESP.restart();
        } else {
          Serial.println("Update not finished? Something went wrong!");
        }
      } else {
        Serial.println("Error Occurred. Error #: " + String(Update.getError()));
      }
    } else {
      Serial.println("Not enough space to begin OTA");
      client.flush();
    }
  } else {
    Serial.println("There was no content in the response");
    client.flush();
  }
}
```
[< Back: Tutorial 0 - Arduino Setup](https://github.com/kempisabelmaddie/IoT_PolyU/blob/main/smartwatch/SmartMedication/Tutorial0.md)\
[> Next: Tutorial 2 - Alarm Setup](https://github.com/kempisabelmaddie/IoT_PolyU/blob/main/smartwatch/SmartMedication/Tutorial2.md)
