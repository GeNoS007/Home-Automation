
#include <SoftwareSerial.h>
SoftwareSerial s(5,6);
int sensorPin = A0; // select the input pin for LDR
const int buzzerdoor = 3; 
const int sensordoor = 4;
const int moisture_sensor_pin = A1;
int motor_pin = 9;


int state; // 0 close - 1 open switch

int sensorValue = 0; // variable to store the value coming from the sensor
void setup() {-
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(sensordoor, INPUT_PULLUP);

  pinMode(motor_pin, OUTPUT);
  


  Serial.begin(9600);
s.begin(9600);
}
 
void loop() {

//MOISTURE SENSOR
  float moisture_percentage;
  int sensor_analog;
  sensor_analog = analogRead(moisture_sensor_pin);
  moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
  Serial.print("Moisture Percentage = ");
  Serial.print(moisture_percentage);
  Serial.print("%\n\n");


  if(moisture_percentage<15)
  {
    Serial.print("Need Water\n");
    analogWrite(motor_pin, 255);
    
  }
  else
  {
    Serial.print("No need of water\n");
    analogWrite(motor_pin, 0);
  }


//
  
sensorValue = analogRead(sensorPin); // read the value from the sensor
if(sensorValue<40)
{
  digitalWrite(LED_BUILTIN, HIGH);  
}
else
{
  digitalWrite(LED_BUILTIN, LOW);
}
 


Serial.println("Light sensorValue"); 
Serial.println(sensorValue); //prints the values coming from the sensor on the screen
if(s.available()>0)
{
 s.write(sensorValue );
}

//for door
state = digitalRead(sensordoor);
  
  if (state == HIGH){
    tone(buzzerdoor, 400);
  }
  else{
    noTone(buzzerdoor);
  }
delay(200);



}
