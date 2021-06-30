# Tutorial 1 - Clock Display
A smartwatch must have a time/clock display. The clock display can be easily done by using the given code from M5Stick C Arduino examples. 

## 1) Use Arduino RTC code
RTC is short for <strong>R</strong>eal-<strong>T</strong>ime <strong>C</strong>lock\
<strong>Go to Files > Examples > M5Stick C > Basics > RTC </strong> 

A new window with the file name "RTC" should prompt up. Save this file at your preferred file location.

![image](https://user-images.githubusercontent.com/80112384/123926700-b9d9bb80-d9be-11eb-9bdb-e3ebdf02c129.png)

## 2) Customise your clock
The time needs to be set up, as it may not be the correct time according to your location. Change the following:
| Time        | Variable           |
| ----------- | ------------------ |
| Hours       | TimeStruct.Hours   |
| Minutes     | TimeStruct.Minutes |
| Seconds     | TimeStruct.Seconds | 
| Weekday     | TimeStruct.WeekDay | 
| Month       | TimeStruct.Month   | 
| Date        | TimeStruct.Date    | 
| Year        | TimeStruct.Year    | 



![image](https://user-images.githubusercontent.com/80112384/123929071-0faf6300-d9c1-11eb-8530-ef8be467cfd3.png) \
From the above image:
The hour is set to 18(meaning it is 6pm), the minute is set to 56, the second is set to 10. The time is 18:56:10. If this is not the current time at your location, change the numbers mentioned. \
The date weekday is set to(meaning it is Wednesday), the month is set to 3(meaning it is March), the date is set to 22, the year is set to 2019. The date is the 22nd of March, 2019. If this is not the current date of your location, change the numbers mentioned.

## 3) Result
After customisation, press the "verfiy" button for debugging or directly press "compile" to see the clock. 
The current time at my location is 17:07:02 and date is 30/6/2021 Wednesday, so my clock looks as follow:
![IMG_3727](https://user-images.githubusercontent.com/80112384/123933361-e4c70e00-d9c4-11eb-97e2-dd8197296f0e.jpg)

[< Back: Tutorial 0 - Arduino Setup](https://github.com/kempisabelmaddie/IoT_PolyU/blob/main/smartwatch/pill_alarm_program/Tutorial/Tutorial0.md)\
[> Next: Tutorial 2 - Alarm Setup](https://github.com/kempisabelmaddie/IoT_PolyU/blob/main/smartwatch/pill_alarm_program/Tutorial/Tutorial2.md)
