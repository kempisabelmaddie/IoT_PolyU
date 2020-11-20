#include <ESP8266WiFi.h>

const char* ssid = "IoT-Lib";
const char* password = "libiot6909";

const int red = 15;   //D8 
const int green = 13; //D7 
const int blue = 16;  //D0 

int redvalue = LOW;
int greenvalue = LOW;
int bluevalue = LOW;

WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);

  digitalWrite(red, LOW);
  digitalWrite(blue, LOW);
  digitalWrite(green, LOW);

  //Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  //Start the server
  server.begin();
  Serial.println("Server started");

  //Print IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  
  //Wait until the client sends some data
  WiFiClient client = server.available();
  if(!client){
    return;  
  }
  
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  //Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  //Match the request
  if(request.indexOf("/RedLED=ON")!= -1){
    digitalWrite(red, HIGH);
    redvalue = HIGH;  
  }
  if(request.indexOf("/RedLED=OFF")!= -1){
    digitalWrite(red, LOW);
    redvalue = LOW;  
  }
  if(request.indexOf("/GreenLED=ON")!= -1){
    digitalWrite(green, HIGH);
    greenvalue = HIGH;  
  }
  if(request.indexOf("/GreenLED=OFF")!= -1){
    digitalWrite(green, LOW);
    greenvalue = LOW;  
  }
  if(request.indexOf("/BlueLED=ON")!= -1){
    digitalWrite(blue, HIGH);
    bluevalue = HIGH;  
  }
  if(request.indexOf("/BlueLED=OFF")!= -1){
    digitalWrite(blue, LOW);
    bluevalue = LOW;  
  }

  //Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  
  client.println("<br><br>");
  client.println("<a href=\"/RedLED=ON\"\"><button style=\"background-color: tomato;font-family:verdana;height:180px;width:220px;font-size:46px;color:black;text-align:center\"> Turn Red On </button></a>");
  client.println("<a href=\"/RedLED=OFF\"\"><button style=\"background-color: silver;font-family:verdana;height:180px;width:220px;font-size:46px;color:black;text-align:center\"> Turn Red Off </button></a></br>");

  client.println("<br><br>");
  client.println("<a href=\"/GreenLED=ON\"\"><button style=\"background-color: springgreen;font-family:verdana;height:180px;width:240px;font-size:46px;color:black;text-align:center\"> Turn Green On </button></a>");
  client.println("<a href=\"/GreenLED=OFF\"\"><button style=\"background-color: silver;font-family:verdana;height:180px;width:240px;font-size:46px;color:black;text-align:center\"> Turn Green Off </button></a></br>");

  client.println("<br><br>");
  client.println("<a href=\"/BlueLED=ON\"\"><button style=\"background-color: deepskyblue;font-family:verdana;height:180px;width:200px;font-size:46px;color:black;text-align:center\"> Turn Blue On </button></a>");
  client.println("<a href=\"/BlueLED=OFF\"\"><button style=\"background-color: silver;font-family:verdana;height:180px;width:220px;font-size:46px;color:black;text-align:center\"> Turn Blue Off </button></a></br>");
  client.println("</html>");

  delay(100);
  Serial.println("Client disconnected");
  Serial.println("");
}
