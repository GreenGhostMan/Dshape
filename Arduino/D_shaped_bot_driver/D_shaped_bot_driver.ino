#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#define right_encoderA     19     // (interrupt numbers 1)
#define right_encoderB     38

#define left_encoderA      18     // (interrupt numbers 5)
#define left_encoderB      31     // (interrupt numbers 4)
#define SMOOTH             10
#define sign(x) (x > 0) - (x < 0) // if x>0 --> 1 , if x<0 --> -1, if x=0 --> 0
#define LOOPTIME          100
#define ENA1 8
#define Right_in1 36
#define Right_in2 37
#define ENA2 12
#define Left_in1 34
#define Left_in2 35
#include <Wire.h>
#include <Encoder.h>
#include "robot_specs.h"

volatile long right_count = 0;
volatile long left_count = 0;
long countAnt1 = 0;
long countAnt2 = 0;
double rpm_req1 = 0;
double rpm_req2 = 0;
double rpm_act1 = 0;
double rpm_act2 = 0;
int PWM_val1 = 0;     // right
int PWM_val2 = 0;

void setup() 
{
  Serial.begin(9600);
  //setupEncoders();  
  setupMotors();   
}

void loop() 
{
   //unsigned long time = millis();
//  if (time - lastMilli >= LOOPTIME)   {  // enter timed loop ( 100 ms or greater)

  
   // int x = time - lastMilli;
    //getMotorData(x);

    PWM_val1 = updatePid(1, PWM_val1, rpm_req1, rpm_act1);
    PWM_val2 = updatePid(2, PWM_val2, rpm_req2, rpm_act2);

    if (PWM_val1 > 0 && PWM_val2 > 0) {
      Forward();
    }
    else if (PWM_val1 < 0 && PWM_val2 < 0) {
      Backward();
    }
    else if (PWM_val1 > 0 && PWM_val2 < 0) {
      Right();
    }
    else if (PWM_val1 < 0 && PWM_val2 > 0) {
      Left();
    }
    if (PWM_val1 == 0 && PWM_val2 == 0) {
      Release();
    }
    Serial.print(right_count); 
    Serial.print("bbbbs");
    Serial.println(left_count);
    //setPWM();
    //loat y = x / 1000.0; // millis to seconds
    //sendMessage(y);
    //lastMilli = time;
  }
