#ifndef Led_h
#define Led_h

#include "Arduino.h"


class Led
{
    private:
    byte pin;
    void init();
              

       
        
    public:
    Led(byte pin);
    void IsOn(bool state);
  
        
};

#endif