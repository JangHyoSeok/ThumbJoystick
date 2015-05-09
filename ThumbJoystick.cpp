/*
  ThumbJoystick.cpp - Library for thumb joysticks.
  Created by Juan A. Rossi. 2011-07-24
  Released under the GPL license
*/

#include "WProgram.h"
#include "ThumbJoystick.h"

ThumbJoystick::ThumbJoystick(int selPin, byte xAxisPin, byte yAxisPin, boolean xInvert, boolean yInvert){

  _selPin=selPin;
  _xAxisPin=xAxisPin;
  _yAxisPin=yAxisPin;
  _xInvert=xInvert;
  _yInvert=yInvert;
  _toDigitalValue=THUMBJOYSTICK_NULL;
  _digitalValue=THUMBJOYSTICK_NULL;

  pinMode(_selPin, INPUT);
  digitalWrite(_selPin, HIGH);

}

void ThumbJoystick::setZeros(){
  //calculate calibration values
  delay(100);
  _xZero = analogRead(_xAxisPin);
  delay(100);
  _yZero = analogRead(_yAxisPin);

}


void ThumbJoystick::setZeros(int xZero, int yZero){

  _xZero = constrain(xZero, 0, 1023);
  _yZero = constrain(yZero, 0, 1023);

}


long ThumbJoystick::mapAxis(long x, long in_min, long in_max, long out_min, long out_max){
  return (x - in_min) * (out_max - out_min + 1) / (in_max - in_min + 1) + out_min;
} 

int ThumbJoystick::getAxisValue(int pin, int zero, boolean invert, int out_min, int out_max){
  int result;
  int limit;
  
  limit=min(zero, 1023-zero);
  
  result = constrain(mapAxis(analogRead(pin)-zero, -limit, limit, out_min, out_max), out_min, out_max);
   
  if (invert){
    return -result;
  }
   
  return result; 

} 

int ThumbJoystick::getXAxis(){
   
  return getAxisValue(_xAxisPin, _xZero, _xInvert, -500, 500);

}

int ThumbJoystick::getYAxis(){

  return getAxisValue(_yAxisPin, _yZero, _yInvert, -500, 500);

}

int ThumbJoystick::getXAxisMaped(int out_min, int out_max){
   
  return getAxisValue(_xAxisPin, _xZero, _xInvert, out_min, out_max);

}

int ThumbJoystick::getYAxisMaped(int out_min, int out_max){

  return getAxisValue(_yAxisPin, _yZero, _yInvert, out_min, out_max);

}

void ThumbJoystick::updateDigital(){
  int x = getXAxisMaped(-5, 5);
  int y = getYAxisMaped(-5, 5);
  boolean sel = digitalRead(_selPin);
   
   
  if (x < -3) _toDigitalValue = THUMBJOYSTICK_LEFT;
  if (x > 3) _toDigitalValue = THUMBJOYSTICK_RIGHT;
  if (y < -3) _toDigitalValue = THUMBJOYSTICK_DOWN;
  if (y > 3) _toDigitalValue = THUMBJOYSTICK_UP;
  if (sel == LOW) _toDigitalValue = THUMBJOYSTICK_SEL; 
   
  if ( (x == 0) && (y == 0) && (sel == HIGH) ){
    _digitalValue = _toDigitalValue;
    _toDigitalValue = THUMBJOYSTICK_NULL;
  }
}

byte ThumbJoystick::readDigital(){
  byte result = THUMBJOYSTICK_NULL;

  if (_digitalValue != THUMBJOYSTICK_NULL){
    result = _digitalValue;
    _toDigitalValue = THUMBJOYSTICK_NULL;
    _digitalValue = THUMBJOYSTICK_NULL; 
  }
  
  return result;

}

