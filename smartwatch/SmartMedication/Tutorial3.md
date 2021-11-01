![image](https://user-images.githubusercontent.com/80112384/139670503-da07ddef-c214-49b8-ad24-3615b6751ca8.png)

```arduino
int pinValue = 0;
String pillAmount = ""; 
String pillName = ""; 

BLYNK_WRITE(V0){
  pinValue = param.asInt();
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("Time: %02d : %02d : %02d\n",RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds);
  M5.Lcd.println("Medication Reminder:");
  switch (pinValue) {
    case 1:
      pillAmount = "1"; 
      pillName = "cholesterol "; 
      M5.Lcd.println(pillName + "x " + pillAmount); 
      break;
    case 2:
      pillAmount = "2"; //hereeeeeeee
      pillName = "blood pressure "; //hereeeee
      M5.Lcd.println(pillName + "x " + pillAmount); //hereeeeeeeeeeeeeeee
      break;
    default:
      // statements
      break;
  }
}
```

![image](https://user-images.githubusercontent.com/80112384/139669971-48ace31f-4630-4011-a4d2-6125df662da3.png)
```arduino
int displayer = 0;
```

![image](https://user-images.githubusercontent.com/80112384/139673156-9df4200e-890e-46ee-8cdb-2576d72f9c57.png)
```arduino
displayer = 1;
```

![image](https://user-images.githubusercontent.com/80112384/139673570-d31dcd38-d312-4621-90a8-34393e361a5e.png)
```arduino
if (displayer == 0){ 
  //clock display code
}
```

![image](https://user-images.githubusercontent.com/80112384/139673737-dd3e5be3-9141-446f-afc4-fd8763742745.png)
```arduino
#define REDLED 10
```

![image](https://user-images.githubusercontent.com/80112384/139673834-858457b8-c5cd-4e6b-b1d9-38836ca35144.png)
```arduino
pinMode(REDLED, OUTPUT);
```

![image](https://user-images.githubusercontent.com/80112384/139674004-0e50d70f-7306-4def-8104-dfe3d9d4532b.png)
```arduino
digitalWrite(REDLED, LOW);
delay(5000);
```

![image](https://user-images.githubusercontent.com/80112384/139674181-1c92c424-ffa4-4801-8ef4-f67f6df6d216.png)
```arduino
const int servo_pin = 26;
int freq = 50;
int ledChannel = 0;
int resolution = 10;
extern const unsigned char m5stack_startup_music[];
```

![image](https://user-images.githubusercontent.com/80112384/139674367-977f5bda-6724-42b6-8b14-906138657ce1.png)
```arduino
ledcSetup(ledChannel, freq, resolution);
ledcAttachPin(servo_pin, ledChannel);
ledcWrite(ledChannel, 256);//0°
````

![image](https://user-images.githubusercontent.com/80112384/139674498-7cec2682-f826-4f14-8446-74ece34f747a.png)
```arduino
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
```

![image](https://user-images.githubusercontent.com/80112384/139674819-9576675c-d273-4584-90e8-bae4ec82a0a9.png)
```arduino
if (M5.BtnA.wasReleased()){
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setCursor(0, 0);
  displayer = 0;
  delay(3000);
}
```

![image](https://user-images.githubusercontent.com/80112384/139674931-dd772587-81d7-44ec-bf22-6b1be4077a98.png)
```arduino
else{
  //melody playing code
}
```

![image](https://user-images.githubusercontent.com/80112384/139675247-2958d825-325f-4768-a201-8321b695076f.png)
```arduino
digitalWrite(REDLED, HIGH);
ledcWriteTone(ledChannel, 0);
delay(1000);
```
