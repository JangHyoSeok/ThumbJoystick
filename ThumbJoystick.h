/*
  ThumbJoystick.h - Library for thumb joysticks. with non blocking functions
  Created by Juan A. Rossi. 2011-07-24
  Released under the GPL license
*/

#ifndef ThumbJoystick_h
#define ThumbJoystick_h


#if ARDUINO >= 100
#include "Arduino.h"       // for delayMicroseconds, digitalPinToBitMask, etc
#else
#include "WProgram.h"      // for delayMicroseconds
#include "pins_arduino.h"  // for digitalPinToBitMask, etc
#endif


// constans that can be called for comparing digital values
#define THUMBJOYSTICK_NULL 0
#define THUMBJOYSTICK_SEL 1
#define THUMBJOYSTICK_LEFT 2
#define THUMBJOYSTICK_RIGHT 3
#define THUMBJOYSTICK_UP 4
#define THUMBJOYSTICK_DOWN 5

class ThumbJoystick
{
  public:
    // constructor, allows to invert axis to match correct physical orientation
    ThumbJoystick(int selPin, byte xAxisPin, byte yAxisPin, boolean xInvert, boolean yInvert);
    
    // sets the zeros for the axes to current values
    void setZeros();
    
    // set the zeros for the axes to defined values
    void setZeros(int xZero, int yZero);
    
    // returns value between -500 and 500 for the X axis, 0 is defined by functions above
    int getXAxis();
    
    // returns value between -500 and 500 for the Y axis, 0 is defined by functions above
    int getYAxis();
    
    // returns value between the defined min and max for the X axis, 0 is defined by functions above
    int getXAxisMaped(int out_min, int out_max);
    
    // returns value between the defined min and max for the Y axis, 0 is defined by functions above
    int getYAxisMaped(int out_min, int out_max);
    
    // updates internal state for digital values, run as much as you can
    void updateDigital(); 
    
    // read the state for the digital values, returns values maped as constants above
    byte readDigital();	
  
  private:
    byte _selPin;     
    byte _xAxisPin;  
    byte _yAxisPin;
    int _xZero;
    int _yZero;
    boolean _xInvert;
    boolean _yInvert;
    byte _toDigitalValue;
    byte _digitalValue;
    // internal function that does work better than map
    long mapAxis(long x, long in_min, long in_max, long out_min, long out_max);
    // internal function that returns mapped axis, but keeps the 0 on the right position 
    int getAxisValue(int pin, int zero, boolean invert, int out_min, int out_max);
};


#endif
