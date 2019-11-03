#include <Joystick.h>
#include <Arduino.h>

Joystick::Joystick(byte ButtonPin, byte XPin, byte YPin, int deadZone)
{
    this->ButtonPin = ButtonPin;
    this->XPin = XPin;
    this->YPin = YPin;
    this->deadZone = deadZone;
    init();
}

void Joystick::init()
{
    pinMode(this->ButtonPin, INPUT);
}


int Joystick::getSpeedAxisX()
{
     int speed = 0;
     int XmapSpeed = map(analogRead(this->XPin), 0, 4095, -100, 100); //3725
     speed = Deadzonecal(XmapSpeed);
     return speed;

}

int Joystick::getSpeedAxisY()
{
     int speed = 0;
     int YmapSpeed = map(analogRead(this->YPin),4095, 0, -100, 100); //3725
     speed = Deadzonecal(YmapSpeed);
     return speed;

}



int Joystick::Deadzonecal(int mapspeed)
{
    if (mapspeed > this->deadZone || mapspeed < this->deadZone*-1) /// callibriation deadzone
    {
        return mapspeed;
    }
    else
    {
        return 0;
    }
}

bool Joystick::buttonIspressed()
{
    if (digitalRead(ButtonPin) == false)
    {
        delayCount++;
        if (delayCount <= 1)
        {
            isButtonDown = true;
        }
        else
        {
            isButtonDown = false;
        }
    }
    else
    {
        delayCount = 0;
        isButtonDown = false;
    }
    return isButtonDown;
}
