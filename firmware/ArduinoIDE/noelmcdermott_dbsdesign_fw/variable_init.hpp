#pragma once
#include <Arduino.h>



// #define ROTATION_SPEED_V6     //rotation speed (steps/sec) during normal operation ie rotation speed
#define STEPS_PER_REV_V1  3200          //200 * 16 //number of steps/rev (360/1.8 = 200 in this case)
#define R_SENSE           0.11f
#define MAX_VOLT_V14      3.3f 
#define MIN_VOLT_V14      0

#define CLOCKWISE_STEP_FROM_HOME_V3    500          // ASSUME
#define MAX_NUMB_STEP_FROM_HOME_V4     2000         // ASSUME
#define ROTATION_SPEED_STEP_PR_SEC_V6  1000 
#define FAST_SPEED_V2_1                1000 // Speed for fast approach (steps/sec)
#define SLOW_SPEEDV2_3                 500  // Speed for slow withdrawal (steps/sec)

enum Modes {
  TEST_MODE = 0,
  RUN_MODE = 1
};
// extern int HAL_SENSOR_CON_RPM_V8;
// extern int HOME_POSITION_V2_5;
// extern int CURRENT_POSITION_FROM_HOME_V5;
// extern int OVER_CURRENT_V17;
// extern int OVER_RATING_V18;
// extern int POSITION_V2_4;
// extern int POSITION_V_2_2;
// extern int  V7_CONV_AFR_V73;
// extern float CONV_VOLTAGE_V14;
// extern float CONV_CURRENT_V14;

extern int halSensorConRpmV8;
extern int homePositionV2_5;
extern int currentPositionFromHomeV5;
extern int overCurrentV17;
extern int overRatingV18;
extern int positionV2_4;
extern int positionV2_2;
extern float v7ConvAfrV73;
extern float convVoltageV14;
extern float convCurrentV14;

