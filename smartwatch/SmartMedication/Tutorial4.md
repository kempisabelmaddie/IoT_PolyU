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
