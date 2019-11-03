#include <Arduino.h>
#include <Button.h>





Button::Button(byte pin)
    {
     this->pin = pin;
     init();
    } 


void Button::init()
{
   pinMode(pin,INPUT_PULLUP);//
}


bool Button::buttonIspressed()
{            
        if(digitalRead(pin) == false  )
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
 