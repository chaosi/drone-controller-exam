#ifndef Led_h
#define Led_h

#include "Arduino.h"


class Led
{
    private:
    int pin;
    void init();
              

       
        
    public:
    Led(int pin);
    void IsOn(bool state);
  
        
};

#endif