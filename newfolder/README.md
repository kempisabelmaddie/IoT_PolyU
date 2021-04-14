## If Room Temperature Higher than Certain Degree, </br> Then Send Notification to Mobile Phone through IFTTT.</br> Bonus: Send data to Thingsboard

### Notes
This tutorial consists of 2 versions:</br>
Version 1: Connects NCIR to IFTTT, files saved in folder Version_1,</br>
Version 2: Connects NCIR to IFTTT and Thingsboard folder Version_2,</br>
Common files are put in this current directory.</br>

### Demo Video
Click on this YouTube link to watch the demo video<strong> without </strong>Thingsboard.
https://youtu.be/iDBmOskIZCA

Click on this YouTube link to watch the demo video<strong> with </strong>Thingsboard.

### What is IFTTT?
IFTTT stands for "If This Then That", a company that provides a software platform that connects apps, devices and services from different developers, in order to trigger one or more automations involving those apps, devices and services. In this example, we use "If Room Temperature Higher than Certain Degree, Then Send Notification to Mobile Phone through IFTTT". The automations are accomplished via applets that connectS multiple apps to run automated tasks.

### How to measure Room Temperature?
In this project, we use M5Stack's NCIR sensor unit to measure Room Temperature. The UI Flow's Python and Blockly Code is in this folder, named _temperature_IFTTT.m5f_ .

### What is Thingsboard?
ThingsBoard is an open-source server-side platform that allows you to monitor and control IoT device. Features include a database system and a real-time web dashboard, which gives a great visualization of the data to the user.

### Things you need for this project
1) M5Stack Core <br/>
<https://m5stack.com/collections/m5-core/products/grey-development-core>
2) M5Stack NCIR Unit <br/>
<https://m5stack.com/products/ncir-sensor-unit?_pos=2&_sid=c47336460&_ss=r&variant=16804757373018>
3) M5Stack Universal 4Pin Buckled Grove Cable Wire <br/>
<https://m5stack.com/collections/m5-accessory/products/4pin-buckled-grove-cable>
4) USB to Type C Data Transfer Cable <br/>
<https://www.belkin.com/hk/en/p/P-F2CU029/>
5) Install _UIFlow-Desktop-IDE_ (depending on your computer, choose Windows/MacOS/Linus. This tutorial will use Windows)
<https://flow.m5stack.com/> <br/>
6) Install _M5Burner_ (depending on your computer, choose Windows/MacOS/Linus. This tutorial will use Windows)
<https://m5stack.com/pages/download> <br/>
9) Download _temperature_IFTTT.m5f_ from this link <br/>
<https://github.com/kempisabelmaddie/IoT_PolyU/blob/main/newfolder/temperature_IFTTT.m5f>
10) IFTTT Account <br/>
<https://ifttt.com/>
11) If you are going for Version 2, a Thingsboard account and set up is needed.</br>
<https://thingsboard.io/>

### Project Setup
1) Go to the folder and find the file "IFTTT_SetUp.md", or open the file by clicking this link: <br/><https://github.com/kempisabelmaddie/IoT_PolyU/blob/main/newfolder/IFTTT_SetUp.md>
2) Go to the folder and find the file "M5Burner_SetUp.md", or open the file by clicking this link: <br/> <https://github.com/kempisabelmaddie/IoT_PolyU/blob/main/newfolder/M5Burner_SetUp.md>
3) Go to the folder and find the file "TempSensor_SetUp.md", or open the file by clicking this link: <br/><https://github.com/kempisabelmaddie/IoT_PolyU/blob/main/newfolder/TempSensor_SetUp.md>
4) If you are opting for Version 1, follow this link for the rest of the tutorial.
5) If you are opting for Version 2, follow this link for the rest of the tutorial.
