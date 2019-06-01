#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
SoftwareSerial s(D6,D5);
 int lightdata;
 int sensorPin = A0;
 int buzzerPin = 5;
 int sensorValue =0;
 String result="";
// Replace with your network credentials
const char* ssid = "JSN";
const char* password = "12341234";
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
String page = "";
void setup() {
  
Serial.begin(9600); 

s.begin(9600);


pinMode(buzzerPin,OUTPUT);
WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", [](){
    page = "<html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'></head><style> body{background:black;}</style><body><h1 style='color:white'>Sensor to Node MCU Web Server</h1><h3 style='color:white'>Data:</h3> <h4 style='color:white'>"+String(result)+"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Sensor Reading:"+String(sensorValue)+"</h4> <br><br><h1 style='color:white'> Lightdata </h1> <h3 style='color:white'>"+String(lightdata)+"</h3><script>  setTimeout(function () { location.reload(1); }, 1000);</script></body></html>";
    server.send(200, "text/html", page);
  });

   server.begin();
  Serial.println("Web server started!");
}

void loop() {

 
 

 if (s.available()>0)
  {
    lightdata=s.read();
    
  }

 Serial.println(lightdata);
  
  sensorValue =  analogRead(sensorPin);
  if(sensorValue>700)
  {
    result="FIRE DETECTED";
    Serial.println("high");
    tone(buzzerPin,350);
//    delay(1000);
  }
  else
  {
    result="NO FIRE DETECTED";
    noTone(buzzerPin);
  }
  

   Serial.println(sensorValue);
//  delay(1000);
  server.handleClient();
 
  

}
