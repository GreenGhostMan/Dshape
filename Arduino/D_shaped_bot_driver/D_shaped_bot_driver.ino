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

#define ENA1 8                    // PWMC
#define Right_in1 36              // DIRC2
#define Right_in2 37              // DIRC1

#define ENA2 12                   // PWMD
#define Left_in1 34               // DIRD1
#define Left_in2 35               // DIRD2

#include <Wire.h>
#include <Encoder.h>
#include "config.h"
#include "encoder.h"
#include "robot_specs.h"

enum
{
  Start,          // 0
  rpm_req,        // 1
  right_rpm_req,  // 2
  left_rpm_req,   // 3
  Rate,           // 4
  actual_rpm,      // 5
  imu             // 6
};


unsigned long lastMilli = 0;   

double desire_rpm_right = 0;
double actual_rpm_right = 0;

double desire_rpm_left = 0;
double actual_rpm_left = 0;

int right_pwm = 0; 
int left_pwm = 0;

volatile long right_count;
volatile long left_count;
long prev_right_count = 0;
long prev_left_count = 0;






void setup() 
{
  Serial.begin(9600);
  
  setupMotors();   
}

void loop() 
{
  unsigned long time_t = millis();
  if (time_t - lastMilli >= LOOPTIME)   {  // enter timed loop ( 100 ms or greater)


    
    long delta_t = time_t - lastMilli;    
    getMotorData(delta_t);
    float delta_t_sec = delta_t / 1000.0;   
     
    right_pwm = updatePid(1, right_pwm, desire_rpm_right, actual_rpm_right,delta_t_sec);
    left_pwm = updatePid(2, left_pwm, desire_rpm_left, actual_rpm_left,delta_t_sec);

    if (right_pwm > 0 && left_pwm > 0) 
    {
      Forward();
    }
    else if (right_pwm < 0 && left_pwm < 0) 
    {
      Backward();
    }
    else if (right_pwm > 0 && left_pwm < 0) 
    {
      Right();
    }
    else if (right_pwm < 0 && left_pwm > 0) 
    {
      Left();
    }
    if (right_pwm == 0 && left_pwm == 0) 
    {
      Release();
    }  
   
    
    lastMilli = time_t;
  }
}
