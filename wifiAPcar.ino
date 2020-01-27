#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

const char *ssid = "JaiTRC";  //Your SSID here
const char *password = "nopassword";  //Your password
int state=0;

ESP8266WebServer server(80);

void handleRoot() {
    response();
}

void handleSTOP() {
  state=5;
  STOP();
  response();
}
void handleLEFT() {
  state=2;
  left();
  response();
}
void handleFRONT() {
  state=3;
  front();
  response();
}
void handleBACK() {
  state=1;
  back();
  response();
}
void handleRIGHT() {
  state=4;
  right();
  response();
}

const String HtmlHtml = "<html><head>"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" /></head>";
const String HtmlHtmlClose = "</html>";
const String HtmlTitle = "<h1>TRC: Workshop on Robotics and IoT</h1><br/>\n";
const String HtmlStateFront = "<big>CAR is now <b>FRONT</b></big><br/>\n";
const String HtmlStateLeft = "<big>CAR is now <b>LEFT</b></big><br/>\n";
const String HtmlStateBack = "<big>CAR is now <b>BACK</b></big><br/>\n";
const String HtmlStateRight = "<big>CAR is now <b>RIGHT</b></big><br/>\n";
const String HtmlStateStop = "<big>CAR is now <b>STOP</b></big><br/>\n";
const String HtmlButtons = 
    "<a href=\"front\"><button style=\"display: block; width: 100%;\">FRONT</button></a><br/>"
    "<a href=\"left\"><button style=\"display: block; width: 100%;\">LEFT</button></a><br/>"
    "<a href=\"back\"><button style=\"display: block; width: 100%;\">BACK</button></a><br/>"
    "<a href=\"right\"><button style=\"display: block; width: 100%;\">RIGHT</button></a><br/>"
    "<a href=\"stop\"><button style=\"display: block; width: 100%;\">STOP</button></a><br/>";

void response(){
  String htmlRes = HtmlHtml + HtmlTitle;
  if(state == 1){
    htmlRes += HtmlStateBack;
  }
  if(state == 2){
    htmlRes += HtmlStateLeft;
  }
  if(state == 3){
    htmlRes += HtmlStateFront;
  }
  if(state == 4){
    htmlRes += HtmlStateRight;
  }
  if(state == 5){
    htmlRes += HtmlStateStop;
  }
  

  htmlRes += HtmlButtons;
  htmlRes += HtmlHtmlClose;

  server.send(200, "text/html", htmlRes);
}

void setup() {
    delay(1000);
    Serial.begin(9600);
    Serial.println();
    pinMode(D1,OUTPUT);
    pinMode(D2,OUTPUT);
    pinMode(D3,OUTPUT);
    pinMode(D4,OUTPUT);

    WiFi.softAP(ssid, password);

    IPAddress apip = WiFi.softAPIP();
    Serial.print("visit: \n");
    Serial.println(apip);
    server.on("/", handleRoot);
    server.on("/front", handleFRONT);
    server.on("/left", handleLEFT);
    server.on("/back", handleBACK);
    server.on("/right", handleRIGHT);
    server.on("/stop", handleSTOP);
    server.begin();
    Serial.println("HTTP server beginned");
}

void loop() {
    server.handleClient();
}


void front()
{
  digitalWrite(D1,HIGH); 
  digitalWrite(D3,HIGH); 
  digitalWrite(D2,LOW); 
  digitalWrite(D4,LOW);        
}

void back()
{
   digitalWrite(D1,LOW); 
  digitalWrite(D3,LOW); 
  digitalWrite(D2,HIGH); 
  digitalWrite(D4,HIGH);      
}

void left()
{
  digitalWrite(D1,LOW); 
  digitalWrite(D3,HIGH); 
  digitalWrite(D2,LOW); 
  digitalWrite(D4,LOW); 
}

void right()
{
  digitalWrite(D1,HIGH); 
  digitalWrite(D2,LOW); 
 digitalWrite(D3,LOW); 
  digitalWrite(D4,LOW);         
}

void STOP()
{
  digitalWrite(D1,LOW); 
  digitalWrite(D3,LOW); 
  digitalWrite(D2,LOW); 
  digitalWrite(D4,LOW);   
}
