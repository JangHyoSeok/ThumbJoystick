/*
Demostrates the use of the ThumbJoystick library for digital style control applications

Joystick needs to return to 0 to get a value, it won't repeat

A5 goes to the sel pin, no need of pull up, internal activated
A6 the X axis potentiomenter
A7 the Y axis potentiometer

X axis is not inverted
Y axis is inverted

*/
#include <ThumbJoystick.h>

ThumbJoystick joystick(A5, A6, A7, false, true);

void setup(){
  Serial.begin(9600);
  joystick.setZeros();
}

void loop(){
 
  joystick.updateDigital();
  
  byte joystickread = joystick.readDigital();
    if (joystickread != THUMBJOYSTICK_NULL){
      Serial.print("Digital:");
      switch (joystickread) {
	case THUMBJOYSTICK_UP: Serial.println("UP"); break;
	case THUMBJOYSTICK_DOWN: Serial.println("DOWN"); break;
	case THUMBJOYSTICK_RIGHT: Serial.println("RIGHT"); break;
	case THUMBJOYSTICK_LEFT: Serial.println("LEFT"); break;
	case THUMBJOYSTICK_SEL: Serial.println("SEL"); break;
      } 
    }  

}
