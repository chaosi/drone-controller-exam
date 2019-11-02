#include <Joystick.h>
#include <Arduino.h>

Joystick::Joystick(byte ButtonPin, byte XPin, byte YPin, int xCalibrate, int yCalibrate, int deadZone)
{
    this->ButtonPin = ButtonPin;
    this->XPin = XPin;
    this->YPin = YPin;
    this->xCalibrate = xCalibrate;
    this->yCalibrate = yCalibrate;
    this->deadZone = deadZone;
    init();
}

void Joystick::init()
{
    pinMode(ButtonPin, INPUT);
}





int Joystick::getSpeedAxis(int axis) // 0 = X axis     1= Y axis
{
    int speed = 0;

    if (axis == 0)
    {
        XmapSpeed = map(analogRead(XPin), 0, xCalibrate, -100, 100); //3725
        speed = mappedSpeed(XmapSpeed);
    }
    else if (axis == 1)
    {
        YmapSpeed = map(analogRead(YPin), yCalibrate, 0, -100, 100); //4095 2935
        speed = mappedSpeed(YmapSpeed);
    }

    if(speed > 100)
    {
        speed = 100;
    }

    if(speed < -100)
    {
          speed = -100;
    }

   

    return speed;
}

int Joystick::mappedSpeed(int mapspeed)
{
    if (mapspeed > deadZone || mapspeed < -deadZone) /// callibriation deadzone
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
