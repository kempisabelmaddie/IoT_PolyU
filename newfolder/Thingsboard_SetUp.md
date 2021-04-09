## Thingsboard Setup
Note: This tutorial is for users who do have a Thingsboard account. If you don't, visit this link to install it.</br>
https://thingsboard.io/docs/installation/

1) In this tutorial, it uses localhost and is logged into the tenant account.
<img src="https://user-images.githubusercontent.com/80112384/114131905-fd7bd680-9935-11eb-9399-8a7635018f34.jpg">

2) Go to devices on the left column.
<img src="https://user-images.githubusercontent.com/80112384/114132081-49c71680-9936-11eb-92d3-608f5acc2650.jpg">

3) Add a device.
<img src="https://user-images.githubusercontent.com/80112384/114132233-8e52b200-9936-11eb-98e9-0d87a10cf7d0.jpg">
<img src="https://user-images.githubusercontent.com/80112384/114132440-f1444900-9936-11eb-87f2-19781fc36bf2.jpg">

4) Type "NCIR" in the name and press "Add" (Skip the manual credentials setup, it will be set up automatically). 
<img src="https://user-images.githubusercontent.com/80112384/114132765-8c3d2300-9937-11eb-8b32-b578c23c565c.jpg">

5) You should be able to see your NCIR device on the screen.
<img src="https://user-images.githubusercontent.com/80112384/114132977-e211cb00-9937-11eb-9e65-0be2f5ac4240.png">

6) Click on the newly added device and press "Copy Access Token".
<img src="https://user-images.githubusercontent.com/80112384/114133616-e4c0f000-9938-11eb-986e-d89599bd16ec.jpg">

7) Replace "(Your Access Token)" with the copied access token in your code.
<img src="https://user-images.githubusercontent.com/80112384/114134577-90b70b00-993a-11eb-97d6-b2e8d4e3b823.png">

8) Press the "Run" button at the top right hand corner.
<img src='https://user-images.githubusercontent.com/80112384/113992959-86d3d000-9886-11eb-934d-2d5f794f3742.jpg'>

9) See results on the M5Stack Core, the temperature is shown. At the same time, the temperature value is sent to Thingsboard, you can check by clicking on "Latest telemetry".
<img src="https://user-images.githubusercontent.com/80112384/114135233-89dcc800-993b-11eb-8135-8ea9a2991af8.jpg">
