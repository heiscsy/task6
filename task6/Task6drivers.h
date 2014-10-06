//
//  Task6driver.h
//  
//
//  Created by William Ku on 10/6/14.
//
//

#ifndef _Task6driver_h
#define _Task6driver_h

#include "Arduino.h"

/* Pin mappings */
#define SERVO_PWM   6
#define MOTOR_PWM   11
#define MOTOR_L1    12
#define MOTOR_L2    13
#define STEP_1      7
#define STEP_2      8
#define STEP_3      9
#define STEP_4      10
#define SONIC_TRIG  14
#define SONIC_ECHO  15
#define IR_READ     "A0"
#define ENCODER_A   18
#define ENCODER_B   19
#define PUSH        16
#define SLOT        17

/* Physical parameters */
#define EDGE_PER_CYCLE 4.0
#define COUNT_PER_REV 90.0
#define SEC_PER_MIN 60.0

/* Setup */
// Initiation function to instantiate handles.
void initTask5Drivers();

/* Actuators */
// Sets servo angle in degrees.
void setServoAngle(int angle_deg);
// Sets the DC motor speed in rpm (right now direction information is included as +/-); P-velocity control is included.
void setDCSpeed(int speed_rpm);
// Sets stepper motor speed in degrees; stepper will move "angel_deg" degrees every one second.
void setStepperAngle(int angle_deg);

/* Sensors */
// Returns the ultrasonic sensor readings in mm (for accuracy).
int getSonicDistance_mm();
// Returns the infrared sensor readings in mm (for accuracy).
int getIRDistance_mm();
// Returns the DC motor encoder speed readings in rpm (direction is included as +/-).
int getDCSpeed_rpm();
// Administers P-velocity control
void velocityControl();
// Returns true if the push button is pushed; false otherwise.
bool isPushedButton();
// Returns true if the slot switch is triggered/blocked; false otherwise.
bool isTriggeredSlot();

#endif
