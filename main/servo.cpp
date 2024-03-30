#include "servo.h"
#include <Servo.h>

void activateServo(Servo motor){
  motor.write(180);
  delay(1000);
  motor.write(30);
}
