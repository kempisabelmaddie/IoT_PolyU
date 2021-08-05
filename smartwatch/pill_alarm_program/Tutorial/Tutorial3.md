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

According to the official Arduino website, we use "digitalWrite" to turn the LED light on and off, the source can be found here:
https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/

Write the following 2 lines to the BLYNK_WRITE function:

```Arduino
digitalWrite(REDLED, LOW);
delay(5000);
```
![image](https://user-images.githubusercontent.com/80112384/128208194-45a28512-d277-4217-91e1-30c77bab07ff.png)


## 3) Turn Buzzer on (LATER)
https://github.com/m5stack/M5StickC/blob/master/examples/Hat/SPEAKER/SPEAKER.ino
https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/docs/UIFlow-StickC-Book-English.pdf

## 4) Turn off button


[< Back: Tutorial 2 - Clock Display](https://github.com/kempisabelmaddie/IoT_PolyU/blob/main/smartwatch/pill_alarm_program/Tutorial/Tutorial2.md)\
[> Next: Tutorial 4 - Google Sheets](https://github.com/kempisabelmaddie/IoT_PolyU/blob/main/smartwatch/pill_alarm_program/Tutorial/Tutorial4.md)
