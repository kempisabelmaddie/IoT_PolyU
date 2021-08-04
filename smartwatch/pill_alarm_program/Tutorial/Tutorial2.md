# Tutorial 2 - Alarm Setup
The smartwatch will light up to notify pill-taking time, informing the elderly which pill to take. After the button is pressed, the light will turn off, until the next alarm goes off again.

As an example, the elderly Isabel has <strong>high cholesterol</strong> and <strong>glucose level</strong>. Her pill-taking schedule is as follow:\
<strong>Monday Wednesday @13:00 glucose pill x1</strong> \
<strong>Tuesday Thursday @09:00 cholestorol pill x1, @20:00 cholesterol pill x1 </strong>

In order for the smartwatch to light up and receive the appropriate message, we will need to use the app <strong>Blynk</strong> to make a schedule.

## 1) Blynk install and setup
Note: This tutorial only works for Android smartphone users.\
The Blynk app is for inputting the pill-taking schedule. Follow these sections in the tutorial with this link: 
https://docs.blynk.cc/#downloads \
![image](https://user-images.githubusercontent.com/80112384/123949337-07f9b980-d9d5-11eb-9189-8f826eae011f.png)

## 2) Blynk Widget Settings
After receiving your authentication token, we add the widgets to the empty canvas. Tap anywhere on the canvas to open the widget box. All the available widgets are located there. Choose these widgets:
1) Eventor x 1
2) Labeled Value x 2
3) Value Display x 2
4) Level H x 2 

Total widget balance needed: 2,100

Note: If you do not have enough energy balance to select all the widgets, not all the widgets are necessary as some of them are used for better UI design. Yet, the <strong>Eventor</strong> is a must. If you do not know which to choose, continue reading and choose the widgets you would like to keep.

To open each widget settings, click on the widget to prompt the settings page.
Follow the settings below:
### 1) Eventor 
This part will be explained in part <em> 3) Timetable input </em>

### 2) Labeled Value
![Screenshot_2021-06-30-19-26-32-272_cc blynk](https://user-images.githubusercontent.com/80112384/123954101-90c72400-d9da-11eb-98ef-aa2239fb6a15.jpg)
![Screenshot_2021-06-30-19-28-06-486_cc blynk](https://user-images.githubusercontent.com/80112384/123954952-9b35ed80-d9db-11eb-892c-95238feccb6d.jpg)

### 3) Value Display
![Screenshot_2021-06-30-19-27-50-606_cc blynk](https://user-images.githubusercontent.com/80112384/123954317-d7b51980-d9da-11eb-9cba-c000266345fd.jpg)
![Screenshot_2021-06-30-19-40-41-770_cc blynk](https://user-images.githubusercontent.com/80112384/123954839-704b9980-d9db-11eb-933e-2d107f1a66ef.jpg)

### 4) Level H
![Screenshot_2021-06-30-19-28-14-669_cc blynk](https://user-images.githubusercontent.com/80112384/123955072-c91b3200-d9db-11eb-81de-5213d98a2839.jpg)
![Screenshot_2021-06-30-19-28-23-671_cc blynk](https://user-images.githubusercontent.com/80112384/123955080-ca4c5f00-d9db-11eb-99ad-f706dc79f250.jpg)

### Final canvas layout
![Screenshot_2021-06-21-11-16-27-535_cc blynk (1)](https://user-images.githubusercontent.com/80112384/123961097-96286c80-d9e2-11eb-8d45-8eda301e1ca6.jpg)

## 3) Timetable input
Reviewing the elderlies' schedule:\
<strong>Monday Wednesday @13:00 glucose pill x1</strong> \
<strong>Tuesday Thursday @09:00 cholestorol pill x1, @20:00 cholesterol pill x1 </strong> 

Let us first input the time and weekdays for taking the glucose pill. 

### 1) Add New Event
One event is set to <strong>one</strong> certain <strong>time</strong>, but can occur at <strong>multiple days</strong>. 

Click on the Eventor widget and press "Add New Event" to add \
![giphy](https://user-images.githubusercontent.com/80112384/124075706-df76cb80-da77-11eb-8a71-85fe32a898a0.gif)

### 2) Set the date and time (When time turns to...)
Click on "Time", all weekdays and a time widget will show. By default, all dates are selected. As the eldery only takes the glucose pills on Mondays and Wednesday, we deselect all the other weekdays. \
![date](https://user-images.githubusercontent.com/80112384/124079953-59a94f00-da7c-11eb-8bab-a463c8ad253b.gif) \
Then, click on the time widget and choose 1pm (13:00) for taking the glucose pill. \
![time](https://user-images.githubusercontent.com/80112384/124080737-4945a400-da7d-11eb-99d9-47ef9ee3c9ee.gif)

### 3) Set Virtual Pin Value (...then set pin value to...)
When the time turns to 13:00, it needs to send a message to the smartwatch, indicating it is time to take the glucose pill. \
In Blynk, we use the mechanism of setting a <strong>virtual</strong> pin value to simulate the action of sending a message.\
Hence, we need to set the virtual pin <strong>V0</strong> value. \
![setpin](https://user-images.githubusercontent.com/80112384/124081804-8f4f3780-da7e-11eb-87de-10373533c63b.gif) 

Each pin value(number) indicates different pills: 

"1" means glucose pills \
"2" means cholesterol pills 

Right now, we are setting the time for <strong>glucose pill</strong>, so we set the message to <strong>"1"</strong>. \
![to1](https://user-images.githubusercontent.com/80112384/124083090-0cc77780-da80-11eb-87cd-54ec3b561436.gif)

### 4) Repeat this process for the rest of the schedule
The time and date for taking glucose pill is set! Now repeat steps 1 to 3 for the cholesterol pills. \
~~Monday Wednesday @13:00 glucose pill x1~~ \
<strong>Tuesday Thursday @09:00 cholestorol pill x1, @20:00 cholesterol pill x1</strong> 

## 5) Connect Arduino to Blynk
Include the Blynk library in Arduino by going to <strong>Sketch > Include Library > Manage Libraries</strong>.
Type "Blynk" and press "Install".
![image](https://user-images.githubusercontent.com/80112384/124348673-d4f63680-dc1d-11eb-89c0-352bdc4d6ddf.png)\
If you are unable to find the "Blynk" library, follow this YouTube video to install it.\
https://www.youtube.com/watch?v=5lH19LrQl5Y \
Then, we need to connect Arduino to Blynk by WiFi, so we need to include their library headers, WiFi credentials and Blynk's authentication token.\
Copy and paste the following code to Arduino, <strong>remember to change "YourAuthToken", "YourNetworkName" and "YourPassword" to your own's</strong>.
```Arduino
#define BLYNK_PRINT Serial
#include <WiFi.h>
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
![image](https://user-images.githubusercontent.com/80112384/124349061-e0e2f800-dc1f-11eb-9314-011b99534187.png)
Taking connecting your phone to the WiFi as an example, without pressing the "OK" or "Connect" button on your phone, even after you typed the WiFi password, it will not connect to the internet. Similarly, if you only added the WiFi credentials and authentication token, but did not add them in the "setup" and "loop" function, it will not connect to the internet either. Add the highlighted code to your current code:
```Arduino
Blynk.begin(auth, ssid, pass);
```
![image](https://user-images.githubusercontent.com/80112384/128125954-c83ee890-5075-4dae-bf9f-80d834da42da.png)
```Arduino
Blynk.run();
```
![image](https://user-images.githubusercontent.com/80112384/128125997-1ce7547e-d8ef-4e0a-bca7-5fecb9cb5ea5.png)

The next step is to instruct Arduino to read notifications from the Blynk App. To do so, Arduino needs to read the virtual pins from Blynk App, so we will 

## 6) Change Display
## 7) Turn off Button

[< Back: Tutorial 1 - Clock Display](https://github.com/kempisabelmaddie/IoT_PolyU/blob/main/smartwatch/pill_alarm_program/Tutorial/Tutorial1.md)\
[> Next: Tutorial 3 - Google Sheets](https://github.com/kempisabelmaddie/IoT_PolyU/blob/main/smartwatch/pill_alarm_program/Tutorial/Tutorial3.md)
