#pragma once

#define RED_LED                         38
#define GREEN_LED                       39
#define STATUS_02_LED                   40
#define RUN_LED                         41
#define TEST_LED                        42
#define BUZZER_PIN                       5
#define KILL_RELAY_V10                   4
#define LAMBDA_CS1_PIN                  16
            
#define MODE_SELECT_V12                 6
#define EXTERNAL_INPUT                  1
#define LIMIT_SWITCH                    47
#define RESET_V9                        48
        
#define DRIVER_POWER_V11                11        // Enable PIN
#define MAX_DRIVER_CURRENT_V16          20        //(20mA) maximum allowable driver current
        
#define STEPS_PER_REV_V1               3200          //200 * 16 //number of steps/rev (360/1.8 = 200 in this case)
#define R_SENSE                        0.11f
#define MAX_VOLT_V14                   3.3f 
#define MIN_VOLT_V14                   0.0

#define CLOCKWISE_STEP_FROM_HOME_V3    500          // ASSUME
#define MAX_NUMB_STEP_FROM_HOME_V4     2000         // ASSUME
#define ROTATION_SPEED_STEP_PR_SEC_V6  1000 
#define FAST_SPEED_V2_1                1000 // Speed for fast approach (steps/sec)
#define SLOW_SPEEDV2_3                 500  // Speed for slow withdrawal (steps/sec)

enum Modes {
  TEST_MODE = 0,
  RUN_MODE = 1
};

extern int   halSensorConRpmV8;
extern int   homePositionV2_5;
extern int   currentPositionFromHomeV5;
extern int   positionV2_4;
extern int   positionV2_2;
extern float v7ConvAfrV73;
extern float convVoltageV14;
extern float convCurrentV14;