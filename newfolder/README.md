## If Room Temperature Higher than Certain Degree, Then Send Notification to Mobile Phone through IFTTT

### What is IFTTT?
IFTTT stands for "If This Then That", a company that provides a software platform that connects apps, devices and services from different developers, in order to trigger one or more automations involving those apps, devices and services. In this example, we use "If Room Temperature Higher than Certain Degree, Then Send Notification to Mobile Phone through IFTTT". The automations are accomplished via applets that connectS multiple apps to run automated tasks.

### How to measure Room Temperature?
In this project, we use M5Stack's NCIR sensor unit to measure Room Temperature. The UI Flow's Python and Blockly Code is in this folder, named _temperature_IFTTT.m5f_ .

### Things you need for this project
1) M5Stack Core <br\>
<https://m5stack.com/collections/m5-core/products/grey-development-core>
2) M5Stack NCIR Unit <br\>
<https://m5stack.com/products/ncir-sensor-unit?_pos=2&_sid=c47336460&_ss=r&variant=16804757373018>
3) M5Stack Universal 4Pin Buckled Grove Cable Wire <br\>
<https://m5stack.com/collections/m5-accessory/products/4pin-buckled-grove-cable>
4) USB to Type C Data Transfer Cable <br\>
<https://www.belkin.com/hk/en/p/P-F2CU029/>
5) UI Flow V1.7.2 on Browser (Desktop Application can be used as well, this tutorial only covers the browser version)
<https://flow.m5stack.com/> <br\>
6) Install M5Burner (depending on your computer, choose Windows/MacOS/Linus. This tutorial will use Windows)
<https://m5stack.com/pages/download> <br\>
9) Download _temperature_IFTTT.m5f_ from this folder <br\>
<>
10) IFTTT Account <br\>
<https://ifttt.com/>

### IFTTT Setup Tutorial
After setting up an account for IFTTT, follow the steps below.
1) Go to "Create"
  <img src="https://user-images.githubusercontent.com/56757186/109113658-8b7d7280-7777-11eb-980f-6863fb197c62.jpg" width="1000" height="239">
2) Go to "If This"
  <img src="https://user-images.githubusercontent.com/56757186/110071077-58119800-7db6-11eb-8e3c-a185b88c86b5.png" width="1000" height="340">
3) Search "Webhook"
  <img src="https://user-images.githubusercontent.com/56757186/110071284-b9396b80-7db6-11eb-9187-5b28fb7b4239.png" width="1000" height="340">
4) Choose "Receive Web Request"
  <img src="https://user-images.githubusercontent.com/56757186/110071532-2b11b500-7db7-11eb-9cd4-1bea8e4e6e33.png" width="1000" height="340">
5) Type in the event name of your choice. In this example, we will use "temperature"<br/>
6) Click "Create Trigger"
  <img src="https://user-images.githubusercontent.com/56757186/110071781-9fe4ef00-7db7-11eb-8f4e-b3822f45f12d.png" width="1000" height="320">

### Setup Tutorial
