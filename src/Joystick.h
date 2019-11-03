#ifndef Joystick_h
#define Joystick_h

#include "Arduino.h"


using namespace std;

class Joystick 
{

    private:
        
        void init();
        byte ButtonPin;
        byte XPin;
        byte YPin;
        bool isButtonDown;
        int  deadZone;
        int Deadzonecal(int mapspeed);   
        int delayCount;
       


    public:
       Joystick(byte ButtonPin,  byte XPin, byte YPin, int deadZone);              
        bool buttonIspressed();    
        int getSpeedAxisX();
        int getSpeedAxisY();
     
       
        
        
       
        
    
        
};


#endif