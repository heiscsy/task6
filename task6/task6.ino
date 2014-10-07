//this is the main code for task 6 MSRD project
//created on 4th Oct.
//Created by Yuhan Long
//this work belongs to evolutus
//all right reserved 
#include <TimerOne.h>
#include <stdlib.h>
#include "Task6Drivers.h"

//int BUTTON=;
//int SLOT=;



char time200 = 0;
//public char time4 = 0;
int sonicValue=0;
int irValue=0;
int encoderSpeed = 0;
int ButtonBuf= 0;
int buttonPush =0;


char dcWorkingState= 0;

boolean buttonValue= false;
boolean slotValue= false;
int SerialState=0;

//Seriadelay signal, 1 for 0.005s
char Serialdelay = 0;

// this is variables used in Serial communication
char CharReceived = 0;
int ValReceived=0;

void timerInterrupt(){
  //read switch at a granulartiy of 0.02s
  //take serial communication every 0.1s
  static int timer_count = 0;
  Serialdelay++;
  timer_count++;
  if(timer_count % 4 ==0){
    ButtonBuf = ButtonBuf*2 + isPushedButton();
    if (ButtonBuf==15){
        buttonPush = 1;
      }
    }

  if(timer_count ==200) {
    //0.1 secound reached
    time200 = 1;
    timer_count = 0;      
    }
}

void setup(){  
 //for setup code of pins and interrupts.
 Timer1.initialize(5000);//set the timer interrupt at 100ms
 Timer1.attachInterrupt(timerInterrupt);
 Serial.begin(9600);
 
 //pinMode(BUTTON, INPUT);
 //pinMode(SLOT, INPUT);

 //set other output 
}

void sendData(){
  //send IR distance to computer
  Serial.write("I");
  Serial.write(irValue);
  Serial.print("\n"); 
  //send Sonor distance to computer
  Serial.write("X");
  Serial.write(sonicValue);
  Serial.print("\n"); 
  //send encoder Value
  Serial.write("W");
  Serial.write(encoderSpeed);
  Serial.print("\n");
  //send button state
  Serial.write("B");
  Serial.write(buttonValue);
  Serial.print("\n"); 
  //send slotswitch state
  Serial.write("S");
  Serial.write(slotValue);
  Serial.print("\n"); 
}

void readSensor(){
  //receive IR distence
  irValue= getIRDistance_mm();
  //receive ultrasonic distance 
  sonicValue = getSonicDistance_mm();
  //receive encoder data
  encoderSpeed = getDCSpeed_rpm();
  //read button state
  buttonValue = buttonPush;
  buttonPush = 0;
    
    
  //read slotswitch state
  slotValue = isTriggeredSlot();
}


void loop(){
  //read the serial input and report data to the server.
  if(time200 == 1){
    readSensor();
    sendData();    
    time200 = 0;
    }
  //Check serial port
  int len = Serial.available();                                                              
  if ((Serial.available() >0 )&&(SerialState == 0)) {                             //when the serial input is ready                                 
    CharReceived=Serial.read();                                                   //read the character
    if ((CharReceived == 'a' )||(CharReceived == 'w') ||(CharReceived == 's')||('p')) {  //if it is in the char list, transist the serial state into 1, reset the delay signal
      SerialState = 1;
      Serialdelay=0;
    }
  }
  
  
  if ((SerialState ==1) && (Serialdelay>1))                                          //if already receive a letter, and 5ms passed
    {
    if (Serial.available() > 0) {                                                      
      ValReceived = Serial.parseInt();
           
      Serial.print(ValReceived);                                   
        switch(CharReceived){
          case 'a': setServoAngle(ValReceived);break;                                //apply the command on motor        
          case 'w': setDCSpeed(ValReceived);dcWorkingState=0;break;
          case 'p': dcWorkingState=1;break;
          case 's': setStepperAngle(ValReceived);break;
          }
        SerialState = 0;                                                              //transist back to receiving letters   
      }   
      else                                                                               //anything else are garbage, return letter polling
      { 
      SerialState=0;   
      } 
    }
    
  //check dc working state
  //0 for set speed, 1 for set angle
  if(dcWorkingState == 0) {
    actuateDC();
    }
    else{
    turnDC();
    }  

}
  
