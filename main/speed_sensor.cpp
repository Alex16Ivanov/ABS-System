#include "speed_sensor.h"

void SpeedSetUp(){
// TIMER SETUP- the timer interrupt allows precise timed measurements of the reed switch
  //for more info about configuration of arduino timers see http://arduino.cc/playground/Code/Timer1
  cli();//stop interrupts

  TCCR2A = 0; // Set entire TCCR2A register to 0
  TCCR2B = 0; // Same for TCCR2B
  TCNT2 = 0;
  // Set timer count for 1kHz increments
  OCR2A = 499; // = (1/1000) / ((1/(16*10^6))*64) - 1
  // Turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS22, CS21, and CS20 bits for 64 prescaler
  TCCR2B |= (1 << CS22) | (1 << CS20);
  // Enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);
  
  sei();//allow interrupts
  //END TIMER SETUP
  
  
}

void displayMPH(float mph,float mph1){
  Serial.println(mph);
  Serial.println(mph1);
  Serial.println("difference");
  Serial.println(mph1-mph);
}





