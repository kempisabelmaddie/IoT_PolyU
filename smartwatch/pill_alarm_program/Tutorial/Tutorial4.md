# Tutorial 4: Google Sheets
The last step is to make a pill-taking record for the elderly, such as what date and time did they take the pills. This function could be useful when the elderly cannot remember clearly, whether they took their pills yet or not. Also, their doctors could use it to check their patient's (elderlies') health record. 

In this tutorial, Google Sheets is used as the record, whenever the elderly presses the turn off button, the date, time, and pill name will be sent to Google Sheets.

## 1) Settings in Google Sheets

### 1) Open Google Sheets
Go to Google Drive and open a Google Sheets.

### 2) Rename 
Rename the Google Sheet in the following 2 places.
### add picture here

### 3) Open script editor
Go to "Tools" and press on "Script Editor".
### add picture here

### 4) Add code to script editor
With reference to this tutorial (https://www.youtube.com/watch?v=KPOFncRDiHQ) and its Github page (https://github.com/stechiez/iot_projects/tree/master/GoogleSpreadSheet_ESP32), copy and paste the code below onto the script editor

```Arduino
function doGet(e){
  Logger.log("--- doGet ---");
 
 var tag = "",
     value = "";
 
  try {
 
    // this helps during debuggin
    if (e == null){e={}; e.parameters = {tag:"test",value:"-1"};}
 
    tag = e.parameters.tag;
    value = e.parameters.value;
 
    // save the data to spreadsheet
    save_data(tag, value);
 
 
    return ContentService.createTextOutput("Wrote:\n  tag: " + tag + "\n  value: " + value);
 
  } catch(error) { 
    Logger.log(error);    
    return ContentService.createTextOutput("oops...." + error.message 
                                            + "\n" + new Date() 
                                            + "\ntag: " + tag +
                                            + "\nvalue: " + value);
  }  
}
 
// Method to save given data to a sheet
function save_data(tag, value){
  Logger.log("--- save_data ---"); 
 
 
  try {
    var dateTime = new Date();
 
    // Paste the URL of the Google Sheets starting from https thru /edit
    // For e.g.: https://docs.google.com/..../edit 
    var ss = SpreadsheetApp.openByUrl("https://docs.google.com/spreadsheets/d/AKfycbzeiVjch6YegJJlMUhLVheS5gOC_am1I5LBqjr1pdbMLfJULbGteQmctkMwy0p1n8zGyw/edit"); //here
    var dataLoggerSheet = ss.getSheetByName("Sheet1");//here
 
 
    // Get last edited row from DataLogger sheet
    var row = dataLoggerSheet.getLastRow() + 1;
 
 
    // Start Populating the data
    dataLoggerSheet.getRange("A" + row).setValue(row -1); // ID
    dataLoggerSheet.getRange("B" + row).setValue(dateTime); // dateTime
    dataLoggerSheet.getRange("C" + row).setValue(tag); // tag
    dataLoggerSheet.getRange("D" + row).setValue(value); // value
 
 
    // Update summary sheet
    summarySheet.getRange("B1").setValue(dateTime); // Last modified date
    // summarySheet.getRange("B2").setValue(row - 1); // Count 
  }
 
  catch(error) {
    Logger.log(JSON.stringify(error));
  }
 
  Logger.log("--- save_data end---"); 
}
```
### 5) Save project
Press this button to save project
### add picture here

### 6) Deploy as web app
Go to "Deploy", press on "New Deployments" and choose "web apps".

Under "Who has access", press on "Anyone", then click "Deploy".

This step would request for your authorisation. If you agree to it, then follow the procedures to complete this step. 

After authorisation, your Deployment ID and Web app URL will be shown. Copy the Deployment ID and press "OK".

### 7) Change link
In the highlighted area, paste the deployment ID that you just copied there.
![image](https://user-images.githubusercontent.com/80112384/134524065-41ca8a07-7a33-4895-b786-057e4e0c079e.png)

### 8) Change Sheet Name
If you named your sheet something other than "Sheet1", change the information in the highlighted area.
![image](https://user-images.githubusercontent.com/80112384/134524310-13a4b021-6035-46fa-86bb-9811f5f7c795.png)


## 2) Send data to Google Sheets
Here, changes need to be made in Arduino.
### 1) Add WiFiClient Library
To add this new library, copy and paste the following code to Arduino.
```Arduino
#include <WiFiClient.h>
```
![image](https://user-images.githubusercontent.com/80112384/134525423-099b5af9-285a-4339-abaf-cecc99dce33e.png)

### 2) Add deployment ID
To identify your excel sheet, the deployment ID needs to be added.
```Arduino
String GOOGLE_SCRIPT_ID = "your deployment ID";
```
![image](https://user-images.githubusercontent.com/80112384/134526331-94c9c486-14c4-4dc3-aec7-b336e9f306f4.png)
