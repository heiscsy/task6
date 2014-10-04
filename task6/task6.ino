//this is the main code for task 6 MSRD project
//created on 4th Oct.
//Created by Yuhan Long
//this work belongs to evolutus
//all right reserved 
#include <TimerOne.h>



//int BUTTON=;
//int SLOT=;


public char time200 = 0;
//public char time4 = 0;

void timerInterrupt(){
  //read switch at a granulartiy of 0.02s
  //take serial communication every 0.1s
  static int timer_count = 0;

  timer_count++;
  if(timer_count % 4 == 0) {
    //0.02 second reached
    ButtonBuf = ButtonBuf * 2 + digitalRead(BUTTON);
    SlotBuf = SlotBuf *2 + digitalRead(SLOT); 
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
 
 pinMode(BUTTON, INPUT);
 pinMode(SLOT, INPUT);
  
}

void sendData(){
  //send IR distance to computer
  //send Sonor distance to computer
  //send Slotswtch action & button action
}

void readSensor(){
  //receive IR distence
  //receive Sonor distance 
}


void loop(){
  //read the serial input and report data to the server.
  if(time200 = 1){
    readSensor();
    sendData();    
    timer200 = 0;
    }
  //Check serial port
  
  //apply the command on motor

}
  
