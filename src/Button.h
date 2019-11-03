#ifndef Button_h
#define Button_h
#include "Arduino.h"



class Button
{
    private:
              
    byte pin;
    byte state;
    int delayCount;
    bool isButtonDown;
    
        
       
        
       
        
    public:
   bool buttonIspressed();
    Button(byte pin);
    void init();      
};

#endif