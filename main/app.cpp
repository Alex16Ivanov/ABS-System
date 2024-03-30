#include "app.h"

void thresholdImport(int threshold, String state){
  if(Serial.available() > 0)  
  {
    threshold = state.toInt();      
    Serial.print(threshold);        
    Serial.print("\n");           
  }                         
}

void radiusImport(float radius,String state){
  if(Serial.available() > 0)  
  {
    radius = float(state.toInt());      
    Serial.print(radius);        
    Serial.print("\n");           
  }                         
}