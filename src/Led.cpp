#include <Arduino.h>
#include <Led.h>


Led::Led(byte pin)
    {
     this->pin = pin;
     init();
    } 


void Led::init()
{
  pinMode(pin,OUTPUT);
}


void Led::IsOn(bool state)
{
    if (state == true)
    {
       digitalWrite(pin, HIGH); 
    }
    else
    {
         digitalWrite(pin, LOW);
        
    }
    
    
 
}