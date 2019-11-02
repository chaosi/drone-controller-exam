#ifndef Button_h
#define Button_h

//#include <string.h>
#include "Arduino.h"
//using namespace std;

class Button
{
    private:
              
    byte pin;
    byte state;
    //byte lastReading;
   // unsigned long lastDebounceTime = 0;
   // unsigned long debounceDelay = 50;
    int delayCount;
    bool isButtonDown;
    
        
       
        
       
        
    public:
   bool buttonIspressed();
    Button(byte pin);
    void init();
    //void update();
    //byte getState();
    //bool isPressed();
        
};

#endif