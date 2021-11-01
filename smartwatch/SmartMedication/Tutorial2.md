![image](https://user-images.githubusercontent.com/80112384/139668084-1dc8e7d8-bcb4-487d-833e-16fd44a011c4.png)

```arduino
#define BLYNK_PRINT Serial
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";
```

![image](https://user-images.githubusercontent.com/80112384/139668218-3e1f2652-1c5e-4933-82e4-75fba54ffab7.png)
```arduino
Blynk.begin(auth, ssid, pass);
```

![image](https://user-images.githubusercontent.com/80112384/139668346-9f5f57a9-7561-4cf2-b3d6-4b0c78ad1a6f.png)
```arduino
Blynk.run();
```

![image](https://user-images.githubusercontent.com/80112384/139668506-82ddad32-9870-45ec-9e4b-1ad13529a9e7.png)
```arduino
String currentTime = "\xF0\x9F\x95\x92" + String(RTC_TimeStruct.Hours) + ":" + String(RTC_TimeStruct.Minutes) + ":" + String(RTC_TimeStruct.Seconds);
String currentDate = "\xF0\x9F\x93\x85" + String(RTC_DateStruct.Date) + "/" + String(RTC_DateStruct.Month)+ "/" +String(RTC_DateStruct.Year);
Blynk.virtualWrite(V1, currentTime);                                    
Blynk.virtualWrite(V2, currentDate);
```

```arduino

```
