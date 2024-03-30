#include "Arduino.h"
#include <Servo.h>
#include "app.h"
#include "speed_sensor.h"


//int servoPin = 10;

int threshold = 40.00;
//////////////////////////////////////////////////////////////////////////////////
//int TxPin = 1;
#define reed A2//pin connected to read switch
#define servoPin A3
Servo motor;
const byte rxPin = 9;
const byte txPin = 8;

//storage variables
int reedVal;
long timer;// time between one full rotation (in ms)
float mph;
float mph1 = 0;
float radius = 13.5;// tire radius (in inches)
float circumference;
String state = "";


int maxReedCounter = 100;//min time (in ms) of one rotation (for debouncing)
int reedCounter;
////////////////////////////////////////////////////////////////
int counter = 0;
float sumMPH = 0;
float maxMPH = 47.68;


void setup() {
  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    state = Serial.readString(); // Reads the data from the serial port
 }
  motor.attach(servoPin);
  reedCounter = maxReedCounter;
  circumference = 2*3.14*radius;
  pinMode(reed, INPUT);

  
  //Serial.write(12);//clear

  void SpeedSetUp();

  

  Serial.begin(9600);

  
}

ISR(TIMER2_COMPA_vect) {//Interrupt at freq of 1kHz to measure reed switch
  reedVal = digitalRead(reed);//get val of A0
  if (reedVal){//if reed switch is closed
    if (reedCounter == 0){//min time between pulses has passed
      mph = (56.8*float(circumference))/float(timer);//calculate miles per hour
      timer = 0;//reset timer
      reedCounter = maxReedCounter;//reset reedCounter
    }
    else{
      if (reedCounter > 0){//don't let reedCounter go negative
        reedCounter -= 1;//decrement reedCounter
      }
    }
  }
  else{//if reed switch is open
    if (reedCounter > 0){//don't let reedCounter go negative
      reedCounter -= 1;//decrement reedCounter
    }
  }
  if (timer > 200){
    mph = 0;//if no new pulses from reed switch- tire is still, set mph to 0
  }
  else{
    timer += 1;//increment timer
  } 
}



void loop() {
  
  
 //print mph once a second
 // displayMPH1();
  //delay(1000);

  // sumMPH = sumMPH + mph;
  // if(sumMPH >= float(maxMPH*3)){
  //     motor.write(180);
  //     delay(1000);
  //     motor.write(30);
  // } else if(counter % 3 == 0){
          // if(counter =! 0){
          //   sumMPH = 0;
          // }
  //     mph1 = mph;
  //     if(mph>=float(0.00)){
   
  //       if(mph1-mph> float(15.00)){
  //         motor.write(180);
  //         Serial.println(" I am activating with difference:");
  //         Serial.println(mph1-mph);
  //         delay(1000);
  //         motor.write(30);
  //         // motor.detach();
  //       }
  //       else{
  //         motor.write(30);
  //       }
  //     }
  //   } else{
   
  //       if(mph1-mph> float(15.00)){
  //         motor.write(180);
  //         Serial.println(" I am activating with difference:");
  //         Serial.println(mph1-mph);
  //         delay(1000);
  //         motor.write(30);
  //         // motor.detach();
  //       }
  //       else{
  //         motor.write(30);
  //       }
  //     
  //   } 
  counter = counter++;


  /////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //print mph once a second
  displayMPH(mph,mph1);
  

   
    if(mph1-mph> float(15.00)){
      motor.write(180);
      Serial.println(" I am activating with difference:");
      Serial.println(mph1-mph);
      delay(1000);
      motor.write(30);
      // motor.detach();
    }
    else{
      motor.write(30);
    }
    
    
  
  sumMPH = sumMPH + mph;
  Serial.println("Sum is");
  Serial.println(sumMPH);
   if(sumMPH >= float(maxMPH*3)){
      motor.write(180);
      delay(1000);
      motor.write(30);
      sumMPH = 0;
    }
  if(counter%3 == 0){
    mph1 = mph;
  }
  counter = counter++;
  
  

  delay(1000);
  



    
  } 
