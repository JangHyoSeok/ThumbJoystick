/*
Demostrates the use of the ThumbJoystick library for analog style control applications

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
  
  Serial.print("X: ");
  Serial.print(joystick.getXAxis());
  Serial.print(" Y: ");
  Serial.print(joystick.getYAxis());
  Serial.print(" X[-1;1]: ");
  Serial.print(joystick.getXAxisMaped(-1, 1));
  Serial.print(" Y[-10;10]: ");
  Serial.println(joystick.getYAxisMaped(-10, 10));
  delay(100);
  
}
