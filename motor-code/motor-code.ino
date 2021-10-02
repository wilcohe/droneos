#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h> 
#include <Servo.h>

Servo motor1; 
double DEG_2_RAD = 0.01745329251;
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

void setup() { 
  
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  motor1.attach(11);
  if (!bno.begin())
  {
    Serial.print("No BNO055 detected");
    digitalWrite(13, HIGH);
    while (1);
  }
  digitalWrite(12, HIGH);
}

void loop() {

  sensors_event_t orientationData , linearAccelData;
  bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
  bno.getEvent(&linearAccelData, Adafruit_BNO055::VECTOR_LINEARACCEL);

  String pose;
  
  pose += String(orientationData.orientation.x);
  pose += ",";
  pose += String(orientationData.orientation.y);
  pose += ",";
  pose += String(orientationData.orientation.z);
  
  Serial.println(pose);
  
} 
