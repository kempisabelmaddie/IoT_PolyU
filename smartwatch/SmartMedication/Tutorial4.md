[< Back: Tutorial 3 - Alarm Setup](https://github.com/kempisabelmaddie/IoT_PolyU/blob/main/smartwatch/SmartMedication/Tutorial3.md)

# Tutorial 4: Google Sheets

# Table of contents
1. [Settings in Google Sheets](#settings)

    1.1 [Open Google Sheets](#open)
    
    1.2 [Rename](#rename)
    
    1.3 [Open script editor](#script)
    
    1.4 [Add code to script editor](#add)
    
    1.5 [Save project](#save)
    
    1.6 [Deploy as web app](#deploy)
    
    1.7 [Change link](#change)
    
    1.8 [Change Sheet Name](#name)
 2. [Send data to Google Sheets](#send)
 
    2.1 [Add WiFiClient Library](#wifi)
    
    2.2 [Add deployment ID](#id)
    
    2.3 [Add Google Sheets Root certificate](#cert)
    
    2.4 [Send data to Google Sheets](#data)
    
    2.5 [Add trigger](#trigger)

The last step is to make a pill-taking record for the elderly, such as what date and time did they take the pills. This function could be useful when the elderly cannot remember clearly, whether they took their pills yet or not. Also, their doctors could use it to check their patient's (elderlies') health record. 

In this tutorial, Google Sheets is used as the record, whenever the elderly presses the turn off button, the date, time, and pill name will be sent to Google Sheets.

## 1) Settings in Google Sheets <a name="settings"></a>

### 1.1) Open Google Sheets <a name="open"></a>
Go to Google Drive and open a Google Sheets.

### 1.2) Rename <a name="rename"></a>
Rename the Google Sheet in the following 2 places.
### add picture here

### 1.3) Open script editor <a name="script"></a>
Go to "Tools" and press on "Script Editor".
### add picture here

### 1.4) Add code to script editor <a name="add"></a>
With reference to this tutorial (https://www.youtube.com/watch?v=KPOFncRDiHQ) and its Github page (https://github.com/stechiez/iot_projects/tree/master/GoogleSpreadSheet_ESP32), copy and paste the code below onto the script editor

```arduino
function doGet(e){
  Logger.log("--- doGet ---");
 
 var pillName = "",
     pillAmount = "";
 
  try {
 
    // this helps during debuggin
    if (e == null){e={}; e.parameters = {pillName:"test",pillAmount:"-1"};}
 
    pillName = e.parameters.pillName;
    pillAmount = e.parameters.pillAmount;
 
    // save the data to spreadsheet
    save_data(pillName, pillAmount);
 
 
    return ContentService.createTextOutput("Wrote:\n  pillName: " + pillName + "\n  pillAmount: " + pillAmount);
 
  } catch(error) { 
    Logger.log(error);    
    return ContentService.createTextOutput("oops...." + error.message 
                                            + "\n" + new Date() 
                                            + "\npillName: " + pillName +
                                            + "\npillAmount: " + pillAmount);
  }  
}
 
// Method to save given data to a sheet
function save_data(pillName, pillAmount){
  Logger.log("--- save_data ---"); 
 
 
  try {
    var dateTime = new Date();
    var timenow = dateTime.toLocaleTimeString(); 
 
    // Paste the URL of the Google Sheets starting from https thru /edit
    // For e.g.: https://docs.google.com/..../edit 
    var ss = SpreadsheetApp.openByUrl("https://docs.google.com/spreadsheets/d/YourScriptID/edit"); 
    var dataLoggerSheet = ss.getSheetByName("Sheet1");
 
 
    // Get last edited row from DataLogger sheet
    var row = dataLoggerSheet.getLastRow() + 1;
 
    // Start Populating the data
    dataLoggerSheet.getRange("A" + row).setValue(row -1); // ID
    dataLoggerSheet.getRange("B" + row).setValue(dateTime); // Date
    dataLoggerSheet.getRange("C" + row).setValue(timenow); // Time
    dataLoggerSheet.getRange("D" + row).setValue(pillName); // Pill Name
    dataLoggerSheet.getRange("E" + row).setValue(pillAmount); // Pill Amount
    
 
 
    // Update summary sheet
    summarySheet.getRange("B1").setValue(dateTime); // Last modified date
  }
 
  catch(error) {
    Logger.log(JSON.stringify(error));
  }
 
  Logger.log("--- save_data end---"); 
}

```

### 1.5) Save project <a name="save"></a>
Press this button to save project
### add picture here

### 1.6) Deploy as web app <a name="deploy"></a>
Go to "Deploy", press on "New Deployments" and choose "web apps".

Under "Who has access", press on "Anyone", then click "Deploy".

This step would request for your authorisation. If you agree to it, then follow the procedures to complete this step. 

After authorisation, your Deployment ID and Web app URL will be shown. Copy the Deployment ID and press "OK".

### 1.7) Change link <a name="change"></a>
In the highlighted area, paste the deployment ID that you just copied there.

![image](https://user-images.githubusercontent.com/80112384/139709729-bb84fed2-c789-4d36-b9eb-2a8ec1ef342e.png)

### 1.8) Change Sheet Name <a name="name"></a>
If you named your sheet something other than "Sheet1", change the information in the highlighted area.
![image](https://user-images.githubusercontent.com/80112384/134524310-13a4b021-6035-46fa-86bb-9811f5f7c795.png)


## 2) Send data to Google Sheets <a name="send"></a>
Here, changes need to be made in Arduino.

### 2.1) Add WiFiClient Library <a name="wifi"></a>
To add this new library, copy and paste the following code to Arduino.

![image](https://user-images.githubusercontent.com/80112384/139692660-353fb3f9-9876-41ab-b6dd-b86ec0a82c16.png)
```arduino
#include <HTTPClient.h>
```

### 2.2) Add deployment ID <a name="id"></a>
To identify your excel sheet, the deployment ID needs to be added.

![image](https://user-images.githubusercontent.com/80112384/139690030-cbde5927-eb8f-46ff-9f32-291f9eae2cd9.png)
```arduino
String GOOGLE_SCRIPT_ID = "your deployment ID";
```

### 2.3) Add Google Sheets Root certificate <a name="cert"></a>
Root certificate is for Google to authenticate your code. Paste the following: 

![image](https://user-images.githubusercontent.com/80112384/139690228-021d1bd7-25a2-4b4a-85e7-84d945867f51.png)
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


### 2.4) Send data to Google Sheets <a name="data"></a>
To send data to Google sheets, paste the "sendData" function, below the loop function:

![image](https://user-images.githubusercontent.com/80112384/139690416-5c90ad87-178d-4b7d-ae51-816cb33f1295.png)
```arduino
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
```

### 2.5) Add trigger <a name="trigger"></a>
Whenever the elderly presses the button, it will act as a trigger and send out the data to Google Sheets.

![image](https://user-images.githubusercontent.com/80112384/139690736-839874f8-e06b-4e37-a84c-38a6cf8e10c2.png)
```arduino
pillName.replace(" ", "");
sendData("pillName="+ pillName +"&pillAmount=" + pillAmount );
```
# Final Result
The final result will look like this:
### add video here

[< Back: Tutorial 3 - Alarm Setup](https://github.com/kempisabelmaddie/IoT_PolyU/blob/main/smartwatch/SmartMedication/Tutorial3.md)
