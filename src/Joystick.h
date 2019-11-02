#ifndef Joystick_h
#define Joystick_h
//#include <string.h>
#include "Arduino.h"
#include "Controller.h"

using namespace std;

class Joystick 
{

    private:
        
        void init();
        byte ButtonPin;
        byte XPin;
        byte YPin;
        bool isButtonDown;
        int  XmapSpeed;
        int  YmapSpeed;
        int  xCalibrate;
        int  yCalibrate;
        int  deadZone;
        int mappedSpeed(int mapspeed);   
        int delayCount;
       


    public:
       Joystick(byte ButtonPin,  byte XPin, byte YPin, int xCalibrate, int yCalibrate, int deadZone);              
        bool buttonIspressed();
        int getSpeedAxis(int axis);
     
       
        
        
       
        
    
        
};


#endif