## Code Explanation
### Flowchart
<p align="center">
  <img src="https://user-images.githubusercontent.com/80112384/114127710-58f59680-992d-11eb-9d87-d29d74c8a9ef.png">
</p>

### Code explanation
<img src="https://user-images.githubusercontent.com/80112384/114128631-614ed100-992f-11eb-9ae2-5756705ed25b.png">
1) Line 11 sets up the WiFi Credentials.
<img src="https://user-images.githubusercontent.com/80112384/113989775-5d657500-9883-11eb-8f2d-f357cebe976c.png">

2) Line 13 sets up the Thingsboard Credentials.
<img src="https://user-images.githubusercontent.com/80112384/113989866-70784500-9883-11eb-8c98-9c296da8fcd5.png">

<img src="https://user-images.githubusercontent.com/80112384/114128795-c30f3b00-992f-11eb-94da-1f5c2ba48028.png">
3) Line 15 sets up the NCIR Unit to the M5Stack.
<img src="https://user-images.githubusercontent.com/80112384/113989928-7ff78e00-9883-11eb-99dc-be4d8197bdb7.png">

<img src="https://user-images.githubusercontent.com/80112384/114128838-e33efa00-992f-11eb-865c-6e98188aeb83.png">
4) Line 17 sets the initial value of the programme variable 'status' to 'cold'.
<img src="https://user-images.githubusercontent.com/80112384/113989986-930a5e00-9883-11eb-9775-7590906a9593.png">

<img src="https://user-images.githubusercontent.com/80112384/114128916-0d90b780-9930-11eb-84d4-014ff062b30c.png">
5) Line 20 starts the while loop.
<img src="https://user-images.githubusercontent.com/80112384/113990068-acaba580-9883-11eb-8c9e-f41eb3dcc127.png">

<img src="https://user-images.githubusercontent.com/80112384/114128968-32852a80-9930-11eb-8342-7ec10daa5999.png">
6) Line 22 retrieves the temperature value from the NCIR unit, Line 23 sets the header message for data transmission, Line 24 sets the temperature data message, Line 25 sends a POST request for data transmission to Thingsboard.
<img src="https://user-images.githubusercontent.com/80112384/113990129-baf9c180-9883-11eb-96e8-6ce5ec824413.png">

<img src="https://user-images.githubusercontent.com/80112384/114129088-711ae500-9930-11eb-86c6-742013676bc8.png">
7) Line 27 checks if the temperature is bigger than or equal to 25, and whether the value of 'status' is cold or not. 
</br>If true, it will go to line 28 to 29, line 28 sends a trigger message to IFTTT, notifying the user of the abnormal temperature.
</br>Otherwise, it will go to line 30 to 31 to check another condition. If the temperature is less than 25 and the value of 'status' is hot, then set 'status' to cold.
<img src="https://user-images.githubusercontent.com/80112384/113991938-8981f580-9885-11eb-9686-efaf3f97aab4.png">

8) The while loop will be infinite, which will not stop unless you unplug the hardware.
