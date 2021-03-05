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
  <img src="https://user-images.githubusercontent.com/56757186/110071077-58119800-7db6-11eb-8e3c-a185b88c86b5.png" width="1000" height="340">
4) Search "Webhook"
  <img src="https://user-images.githubusercontent.com/56757186/110071284-b9396b80-7db6-11eb-9187-5b28fb7b4239.png" width="1000" height="340">
5) Choose "Receive Web Request"
  <img src="https://user-images.githubusercontent.com/56757186/110071532-2b11b500-7db7-11eb-9cd4-1bea8e4e6e33.png" width="1000" height="250">
6) Type in the event name of your choice. In this example, we will use "temperature"<br/>
7) Click "Create Trigger"
  <img src="https://user-images.githubusercontent.com/56757186/109114847-2aef3500-7779-11eb-9ae0-33edf43c8d93.png" width="300" height="239">
