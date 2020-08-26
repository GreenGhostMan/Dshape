#ifndef _ENCODER_H_
#define _ENCODER_H_
#include"config.h"
#include <Encoder.h>

//right_count = 0;
//left_count = 0;
//prev_right_count = -999;
//prev_left_count = -999;

Encoder left_encoder(18,31);
Encoder right_encoder(19,38);

right_count = right_encoder.read();
if (right_count != prev_right_count) {
    prev_right_count = right_count;
    Serial.println(right_count);
  }

left_count = left_encoder.read();
if (left_count != prev_left_count) {
    prev_left_count = left_count;
    Serial.println(left_count);
    
  }


#endif
