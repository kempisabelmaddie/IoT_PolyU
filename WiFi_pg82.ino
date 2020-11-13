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
  delay(10);

  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);

  digitalWrite(red, LOW);
  digitalWrite(blue, LOW);
  digitalWrite(green, LOW);

  //Connect to WiFi netwprk
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

  // put your main code here, to run repeatedly:
 
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

  //Set ledPin according to the request
  //digitalWrite(ledPin, value)

  //Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.print("Led pin is now: ");
  
  if(redvalue == HIGH){
    client.print("On");
  }
  else{
    client.print("Off");
  }
  if(greenvalue == HIGH){
    client.print("On");
  }
  else{
    client.print("Off");
  }
  if(bluevalue == HIGH){
    client.print("On");
  }
  else{
    client.print("Off");
  }
  
  client.println("<br><br>");
  client.println("<a href=\"/RedLED=ON\"\"><button style=\"background-color: red;\"> Turn Red On </button></a>");
  client.println("<a href=\"/RedLED=OFF\"\"><button> Turn Red Off </button></a></br>");

  client.println("<br><br>");
  client.println("<a href=\"/GreenLED=ON\"\"><button> Turn Green On </button></a>");
  client.println("<a href=\"/GreenLED=OFF\"\"><button> Turn Green Off </button></a></br>");

  client.println("<br><br>");
  client.println("<a href=\"/BlueLED=ON\"\"><button> Turn Blue On </button></a>");
  client.println("<a href=\"/BlueLED=OFF\"\"><button> Turn Blue Off </button></a></br>");
  client.println("</html>");

  delay(100);
  Serial.println("Client disconnected");
  Serial.println("");
}
