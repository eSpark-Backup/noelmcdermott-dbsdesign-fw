#pragma once
#include <Arduino.h>

#define ROTATION_SPEED_V6     //rotation speed (steps/sec) during normal operation ie rotation speed
#define STEPS_PER_REV_V1 200  //number of steps/rev (360/1.8 = 200 in this case)
#define R_SENSE 0.11f
#define MAX_VOLT_V14 3.3f
#define MIN_VOLT_V14 0
#define HAL_SENSOR_CON_RPM_V8
#define V7_CONV_AFR_V73

// Declare the variables as extern
extern int OVER_CURRENT_V17;
extern int OVER_RATING_V18;

