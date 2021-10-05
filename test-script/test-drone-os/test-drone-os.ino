#include <Servo.h>

#define MIN_PULSE 1000
#define MAX_PULSE 2000

int motorPin = 11;
Servo motor1; 

void setup() {
  Serial.begin(9600);
  motor1.attach(motorPin, MIN_PULSE, MAX_PULSE);
  motor1.writeMicroseconds(MIN_PULSE);
}

void loop() {
  for (int i=1; i<4; i++){
    if (i%4 == 0){
      motor1.writeMicroseconds(MIN_PULSE);
    }
    else if (i%4 == 1){
      motor1.writeMicroseconds(1333);
    }
    else if(i%4 == 2){
      motor1.writeMicroseconds(1666);
    }
    else{
    motor1.writeMicroseconds(MAX_PULSE);
    }
  }
}
