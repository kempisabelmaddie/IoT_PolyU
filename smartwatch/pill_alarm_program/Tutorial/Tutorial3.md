# Tutorial 3 - Alarm Setup

## 1) Change Watch Display
Here is the important part. When it is time to take the medicine, the watch's(M5Stick) display should change from clock mode, to pill reminders mode.

In tutorial 2's "Set Virtual Pin Value" section, pin V0 is used to turn the pill alarm on or off. Taking tutorial 2 as an example, when the time is 1pm (on Monday or Wednesday), pin v0 would be set to "1", which means it is time to take the glucose pill. Similarly, if the time is 9am (on Tuesday or Thursday), pin v0 would be set to "2", which means it is time to take the cholesterol pill.

Copy and paste this code before the "setup" function. DO NOT ADD THIS INSIDE THE "setup" OR "loop" FUNCTIONS.

If you would like to read more on BLYNK_WRITE, visit this website: https://docs.blynk.cc/#blynk-firmware-blynktimer-blynk_writevpin
```Arduino
int pinValue = 0;

BLYNK_WRITE(V0){
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
}
```
![image](https://user-images.githubusercontent.com/80112384/128189739-e6834a10-54c3-4553-b4c9-a7510b167eff.png)

At this point, the watch's display does not come out as expected. The previous display is mixed with the new display.
### add image here

Therefore, an if-else statement needs to be added to the program, to differentiate when to display the clock, when to display the reminders.

### 1.1) Create a new variable
A variable "displayer" is created for conditional statements. If displayer is 0, display the clock; if displayer is 1, display the reminders. Add this variable definition along with the others.

```Arduino
int displayer = 0;
```
![image](https://user-images.githubusercontent.com/80112384/128211595-72ae93bb-54de-465a-9261-a849090ef5e6.png)

### 1.2) Redefine the variable when the alarm goes off
The BLYNK_WRITE segment is where the variable needs to be redefined as 1

```Arduino
displayer = 1;
```
![image](https://user-images.githubusercontent.com/80112384/128211892-97711cca-aab8-44e5-af51-bce581a6a959.png)

### 1.3) Create if-else statement
The if-else statement is added to "loop" function. 

```Arduino
if (displayer == 0){ 
  //clock display code
}
```
![image](https://user-images.githubusercontent.com/80112384/128212677-ef2dcd7e-2503-4c0b-97fc-27ec36071f82.png)

### add gif/image here


## 2) Turn Red Light on 
For better user experience, adding a red light for illumination can attract the user's attention more. 

### 2.1) Pin number for LED light
The pin number for the red LED light is 10 for M5StickC, this can be found at the back of the device. As you can see from the picture, the yellow box that is used to highlight the part, is where you can find the pin number for the red LED light.
![3_a46785e5-1f9e-460b-9796-cc9265ec3fea_1200x1200](https://user-images.githubusercontent.com/80112384/128193001-ff439fb0-4160-4d81-92ba-3cd5590ee9ab.jpg)

Therefore, a variable "REDLED" is defined to 10 for programming convenience.
```Arduino
#define REDLED 10
```
![image](https://user-images.githubusercontent.com/80112384/128205527-e25a600f-21a0-4c9a-8e5d-37cbccc633e6.png)


### 2.2) Configure LED as output
In arduino, whether the pin is used as input or output, it must be stated in the program, hence "pinMode" is used. In this project, the LED light is an output. As this is considered a setting, we shall put it in the "setup" function. To read more on "pinMode", this website can be visited:
https://www.arduino.cc/reference/en/language/functions/digital-io/pinmode/

```Arduino
pinMode(REDLED, OUTPUT);
```
![image](https://user-images.githubusercontent.com/80112384/128206124-0cd1859e-6517-4456-ad12-f7b855db490d.png)


### 2.3) Turn on light when alarm is on

According to the official Arduino website, we use "digitalWrite" to turn the LED light on and off. LOW means on, HIGH means off. The source can be found here:
https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/

Write the following 2 lines to the BLYNK_WRITE function:

```Arduino
digitalWrite(REDLED, LOW);
delay(5000);
```
![image](https://user-images.githubusercontent.com/80112384/128208194-45a28512-d277-4217-91e1-30c77bab07ff.png)

### add gif/image here

## 3) Turn speaker on
Having the red LED light may not be enough to attract the attention of the user/elderly. With sound, the user can hear the alarm even from a distance. Hence, the speaker unit is attached to the watch, and a melody is played whenever it is time for medicine. The following part is adapted from these 2 links:

1) M5StickC Github repository: arduino code for speaker
https://github.com/m5stack/M5StickC/blob/master/examples/Hat/SPEAKER/SPEAKER.ino

2) M5Stack UIFlow documentation
https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/docs/UIFlow-StickC-Book-English.pdf


### 3.1) PWM to make sounds
PWM stands for Pulse Width Modulation, it is primarily used to control the intensity of an LED light bulb. However, it can also be applied to make varying sounds with a speaker. From the 1st link above, we use the PWM LED functions to program the speaker. Following the link, these lines of code are inserted for variable declarations:
```Arduino
const int servo_pin = 26;
int freq = 50;
int ledChannel = 0;
int resolution = 10;
extern const unsigned char m5stack_startup_music[];
```
![image](https://user-images.githubusercontent.com/80112384/128364353-3bc8b12d-72f6-4d69-a004-14d6c15abfd1.png)

In the "setup" function, these lines of code are needed too:
```Arduino
ledcSetup(ledChannel, freq, resolution);
ledcAttachPin(servo_pin, ledChannel);
ledcWrite(ledChannel, 256);//0°
```
![image](https://user-images.githubusercontent.com/80112384/128364759-47cecc41-799c-4332-9f28-a9181bb23ede.png)


### 3.2) Make a melody
Next, a pleasant melody should be created for the alarm ringtone. As the sound is created by frequency, each musical notes has its own frequency in Hertz(Hz). To find out the frequency for certain notes, it is fortunate that M5Stack published a documentation with it. It does not include all notes, but it has some basic ones. This can be found in the 2nd link above.
![image](https://user-images.githubusercontent.com/80112384/128365737-65990457-d75b-467b-8e0b-ff8c2d5e6c65.png)

The melody created in this tutorial is 
Middle F
Middle A
High C
High D

This melody is only played when it is time to take medicine. The melody will play contiuously inside the "loop" function.

```Arduino
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
![image](https://user-images.githubusercontent.com/80112384/128470246-bb576049-1814-4fed-9722-dfe27dfa1f36.png)

### add gif/video/image here

## 4) Turn off button
After the user is reminded to take the medicine, the user should be able to turn off the sound and LED light, returning back to the clock display. In doing so, the program should include an OFF button for this function. 

### 4.1) Press OFF button to return to clock display
There are 3 buttons on M5StickC: Button A, Button B, and Power ON/OFF button. In this tutorial, we use Button A as our OFF button to return to the clock display. To find the location of each button, refer to the picture below:

![68747470733a2f2f6d35737461636b2e6f73732d636e2d7368656e7a68656e2e616c6979756e63732e636f6d2f696d6167652f6d352d646f63735f636f6e74656e742f636f72652f6d35737469636b635f30312e706e67](https://user-images.githubusercontent.com/80112384/128457495-d2654f59-7646-44c7-a90f-d65b671ae137.png)

In Arduino, it checks whether button A is pressed in every loop in the "loop" function. If true, then return to clock display. As mentioned in the "Change Watch Display" section in this tutorial, if the variable "displayer" is set to 0, it will show the clock display. The code below does exactly this once the off button is pressed.

```Arduino
if (M5.BtnA.wasReleased()){
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setCursor(0, 0);
  displayer = 0;
  delay(3000);
}
```
![image](https://user-images.githubusercontent.com/80112384/128457991-376812ca-2443-47d6-86f3-985b739710a9.png)

Also, add the "else" statement to the melody playing part

```Arduino
else{
  //melody playing code
}
```

![image](https://user-images.githubusercontent.com/80112384/128470615-99704a31-168c-448a-a1ce-e0915e6f507c.png)


### add gif/image here


### 4.2) Turn off LED light and sound
Here, the LED light and sound will be turned off when it returns from reminder to clock display. To turn off the light, LED light settings is set to "HIGH" with "digitalWrite". To turn off the sound, the frequency is set to 0 with "ledcWriteTone". This is added to the block of code for the clock display settings.

```Arduino
digitalWrite(REDLED, HIGH);
ledcWriteTone(ledChannel, 0);
delay(1000);
```
![image](https://user-images.githubusercontent.com/80112384/128461434-ada2180d-fa19-4ac2-8766-410e400b53a8.png)
This is a reference on how to turn off the speaker sound:
https://community.m5stack.com/topic/61/noise-on-speaker

### add gif/image/video here


[< Back: Tutorial 2 - Clock Display](https://github.com/kempisabelmaddie/IoT_PolyU/blob/main/smartwatch/pill_alarm_program/Tutorial/Tutorial2.md)\
[> Next: Tutorial 4 - Google Sheets](https://github.com/kempisabelmaddie/IoT_PolyU/blob/main/smartwatch/pill_alarm_program/Tutorial/Tutorial4.md)
