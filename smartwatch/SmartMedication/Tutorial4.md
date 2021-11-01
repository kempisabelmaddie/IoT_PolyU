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
    var ss = SpreadsheetApp.openByUrl("https://docs.google.com/spreadsheets/d/1izsu3vYVygxHZ0dyEb_Bec0z78Wn8Ox9UgSEXD6ZveY/edit"); //here
    var dataLoggerSheet = ss.getSheetByName("Sheet1");//here
 
 
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

![image](https://user-images.githubusercontent.com/80112384/139690030-cbde5927-eb8f-46ff-9f32-291f9eae2cd9.png)
```arduino
String GOOGLE_SCRIPT_ID = "your deployment ID";
```

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

![image](https://user-images.githubusercontent.com/80112384/139690736-839874f8-e06b-4e37-a84c-38a6cf8e10c2.png)
```arduino
pillName.replace(" ", "");
sendData("pillName="+ pillName +"&pillAmount=" + pillAmount );
```
