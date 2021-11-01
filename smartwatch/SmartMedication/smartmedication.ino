#include <M5StickC.h>
#include <WiFi.h>
#include "time.h"
#include <Update.h>
#define BLYNK_PRINT Serial
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <HTTPClient.h>
#define REDLED 10

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthenticationToken";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourSSID";
char pass[] = "YourPassword";

String GOOGLE_SCRIPT_ID = "YourScriptID";

const char * root_ca=\
"-----BEGIN CERTIFICATE-----\n" \
"MIIDujCCAqKgAwIBAgILBAAAAAABD4Ym5g0wDQYJKoZIhvcNAQEFBQAwTDEgMB4G\n" \
"A1UECxMXR2xvYmFsU2lnbiBSb290IENBIC0gUjIxEzARBgNVBAoTCkdsb2JhbFNp\n" \
"Z24xEzARBgNVBAMTCkdsb2JhbFNpZ24wHhcNMDYxMjE1MDgwMDAwWhcNMjExMjE1\n" \
"MDgwMDAwWjBMMSAwHgYDVQQLExdHbG9iYWxTaWduIFJvb3QgQ0EgLSBSMjETMBEG\n" \
"A1UEChMKR2xvYmFsU2lnbjETMBEGA1UEAxMKR2xvYmFsU2lnbjCCASIwDQYJKoZI\n" \
"hvcNAQEBBQADggEPADCCAQoCggEBAKbPJA6+Lm8omUVCxKs+IVSbC9N/hHD6ErPL\n" \
"v4dfxn+G07IwXNb9rfF73OX4YJYJkhD10FPe+3t+c4isUoh7SqbKSaZeqKeMWhG8\n" \
"eoLrvozps6yWJQeXSpkqBy+0Hne/ig+1AnwblrjFuTosvNYSuetZfeLQBoZfXklq\n" \
"tTleiDTsvHgMCJiEbKjNS7SgfQx5TfC4LcshytVsW33hoCmEofnTlEnLJGKRILzd\n" \
"C9XZzPnqJworc5HGnRusyMvo4KD0L5CLTfuwNhv2GXqF4G3yYROIXJ/gkwpRl4pa\n" \
"zq+r1feqCapgvdzZX99yqWATXgAByUr6P6TqBwMhAo6CygPCm48CAwEAAaOBnDCB\n" \
"mTAOBgNVHQ8BAf8EBAMCAQYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUm+IH\n" \
"V2ccHsBqBt5ZtJot39wZhi4wNgYDVR0fBC8wLTAroCmgJ4YlaHR0cDovL2NybC5n\n" \
"bG9iYWxzaWduLm5ldC9yb290LXIyLmNybDAfBgNVHSMEGDAWgBSb4gdXZxwewGoG\n" \
"3lm0mi3f3BmGLjANBgkqhkiG9w0BAQUFAAOCAQEAmYFThxxol4aR7OBKuEQLq4Gs\n" \
"J0/WwbgcQ3izDJr86iw8bmEbTUsp9Z8FHSbBuOmDAGJFtqkIk7mpM0sYmsL4h4hO\n" \
"291xNBrBVNpGP+DTKqttVCL1OmLNIG+6KYnX3ZHu01yiPqFbQfXf5WRDLenVOavS\n" \
"ot+3i9DAgBkcRcAtjOj4LaR0VknFBbVPFd5uRHg5h6h+u/N5GJG79G+dwfCMNYxd\n" \
"AfvDbbnvRG15RjF+Cv6pgsH/76tuIMRQyV+dTZsXjAzlAcmgQWpzU/qlULRuJQ/7\n" \
"TBj0/VLZjmmx6BEP3ojY+x1J96relc8geMJgEtslQIxq/H5COEBkEveegeGTLg==\n" \
"-----END CERTIFICATE-----\n";


WiFiClient client;

const char* ntpServer     = "ntp.jst.mfeed.ad.jp";
const int time_difference = 8 * 3600; // HONG KONG

bool ntp_setup = false;
RTC_TimeTypeDef RTC_TimeStruct;
RTC_DateTypeDef RTC_DateStruct;

void execOTA(String host, int port, String bin);

int displayer = 0;
int pinValue = 0;
String pillAmount = ""; 
String pillName = ""; 
int total = 0;

const int servo_pin = 26;
int freq = 50;
int ledChannel = 0;
int resolution = 10;
extern const unsigned char m5stack_startup_music[];

BLYNK_WRITE(V0){
  pinValue = param.asInt();
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setCursor(0, 10, 2);
  M5.Lcd.printf("<-- Turn Off Button");
  switch (pinValue) {
    case 1:
      pillAmount = "1"; 
      pillName = "cholesterol "; 
      total = total + 1; 
      break;
    case 2:
      pillAmount = "2"; 
      pillName = "diabetes "; 
      total = total + 2; 
      break;
    default:
      // statements
      break;
  }
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(10, 27);
  M5.Lcd.println(pillName);
  M5.Lcd.setCursor(50, 55);
  M5.Lcd.println("x " + pillAmount); 
  displayer = 1;
  digitalWrite(REDLED, LOW);
  delay(5000);
}

void setup() {
  pinMode(REDLED, OUTPUT);
  Blynk.begin(auth, ssid, pass);
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
  
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(servo_pin, ledChannel);
  ledcWrite(ledChannel, 256);//0°
}

void loop() {
  Blynk.run();
  String currentTime = "\xF0\x9F\x95\x92" + String(RTC_TimeStruct.Hours) + ":" + String(RTC_TimeStruct.Minutes) + ":" + String(RTC_TimeStruct.Seconds);
  String currentDate = "\xF0\x9F\x93\x85" + String(RTC_DateStruct.Date) + "/" + String(RTC_DateStruct.Month)+ "/" +String(RTC_DateStruct.Year);
  Blynk.virtualWrite(V1, currentTime);                                    
  Blynk.virtualWrite(V2, currentDate);

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
  if (displayer == 0){ 
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(40, 5, 2);
    M5.Lcd.println("Simple Clock");
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(27, 20);
    M5.Lcd.printf("%02d:%02d:%02d\n", RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds);
    M5.Lcd.setCursor(27, 55);
    M5.Lcd.setTextSize(1);
    M5.Lcd.printf("%04d-%02d-%02d(%s)\n", RTC_DateStruct.Year, RTC_DateStruct.Month, RTC_DateStruct.Date, wd[RTC_DateStruct.WeekDay]);
    digitalWrite(REDLED, HIGH);
    ledcWriteTone(ledChannel, 0);
    delay(1000);
  }

  else{
    if (M5.BtnA.wasReleased()){
      pillName.replace(" ", "");
      sendData("pillName="+ pillName +"&pillAmount=" + pillAmount );
      if (total == 9){
        total = 0; 
      }
      Blynk.virtualWrite(V3, total);
      delay(5000);
      M5.Lcd.fillScreen(TFT_BLACK);
      M5.Lcd.setCursor(0, 0);
      displayer = 0;
      delay(3000);
    }
    else{
      ledcWriteTone(ledChannel, 349); //middle F
      delay(500);
      ledcWriteTone(ledChannel, 440); //middle A
      delay(500);
      ledcWriteTone(ledChannel, 523); //high C
      delay(500);
      ledcWriteTone(ledChannel, 698); //high D
      delay(500);
      ledcWriteTone(ledChannel, 0); //muted
      delay(500);
    }
  }
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

void sendData(String params) {
   HTTPClient http;
   String url="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?"+params;
   Serial.print(url);
    Serial.print("Making a request");
    http.begin(url, root_ca); //Specify the URL and certificate
    int httpCode = http.GET();  
    http.end();
    Serial.println(": done "+httpCode);
}
