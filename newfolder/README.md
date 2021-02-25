## If Room Temperature Higher than Certain Degree, Then Send Notification to Mobile Phone through IFTTT

### What is IFTTT?
IFTTT stands for "If This Then That", a company that provides a software platform that connects apps, devices and services from different developers, in order to trigger one or more automations involving those apps, devices and services. In this example, we use "If Room Temperature Higher than Certain Degree, Then Send Notification to Mobile Phone through IFTTT". The automations are accomplished via applets that connectS multiple apps to run automated tasks.

### How to measure Room Temperature?
In this project, we use M5Stack's NCIR sensor unit to measure Room Temperature. The UI Flow's Python and Blockly Code is in this folder, named _temperature_IFTTT.m5f_ .

### Setup Tutorial
1) Go to this link <https://ifttt.com/> and setup an account.
2) Go to "Create"
  <img src="https://user-images.githubusercontent.com/56757186/109113658-8b7d7280-7777-11eb-980f-6863fb197c62.jpg" width="1000" height="239">
3) Go to "If This"
  <img src="https://user-images.githubusercontent.com/56757186/109114059-1b232100-7778-11eb-831a-cc96dd7022d3.png" width="300" height="239">
4) Search "Webhook"
  <img src="https://user-images.githubusercontent.com/56757186/109114504-b87e5500-7778-11eb-9bc0-80bedbf05fdf.png" width="350" height="239">
5) Choose "Receive Web Request"
  <img src="https://user-images.githubusercontent.com/56757186/109114728-ff6c4a80-7778-11eb-8e64-f2a19dce0c4e.png" width="190" height="250">
6) Type in the event name of your choice. In this example, we will use "temperature"
7) Click "Create Trigger"
  <img src="https://user-images.githubusercontent.com/56757186/109114847-2aef3500-7779-11eb-9ae0-33edf43c8d93.png" width="300" height="239">
