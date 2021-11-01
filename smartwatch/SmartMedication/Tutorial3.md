![image](https://user-images.githubusercontent.com/80112384/139688520-4cd9d737-3014-4f03-9bd0-8a27dac2d2aa.png)

```arduino
int pinValue = 0;
String pillAmount = ""; 
String pillName = ""; 

BLYNK_WRITE(V0){
  pinValue = param.asInt();
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setCursor(0, 10, 2);
  M5.Lcd.printf("<-- Turn Off Button");
  switch (pinValue) {
    case 1:
      pillAmount = "1"; 
      pillName = "cholesterol "; 
      break;
    case 2:
      pillAmount = "2"; 
      pillName = "diabetes "; 
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

![image](https://user-images.githubusercontent.com/80112384/139688723-d9952f62-58b0-4e9d-9df1-b38275034100.png)
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

![image](https://user-images.githubusercontent.com/80112384/139688923-534f4d80-f29e-4b1b-ab69-d13c70ebc5e2.png)
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
