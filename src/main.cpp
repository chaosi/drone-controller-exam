#include <Arduino.h>
#include <WifiCon.h>
#include <string.h>
#include <WiFiUdp.h>
#include <Button.h>
#include <Joystick.h>
#include <Controller.h>
#include <sstream>
using namespace std;

bool isCommandSent = false;
bool isflying = false;
bool Debug = true;
string commandResponse;
int speedx = 0 ;
int speedy = 0 ;


WifiCon drone;
Button TakeoOffButton(23);
Button landButton(3);
Joystick MoveJoystik(5, 4, 2, 3725,2935, 10);
Joystick rotateJoystik(34,36, 39, 4100, 4100, 37);


byte LCD_COL = 2;
byte LCD_ROW = 16;

long previusDelayBattery;
long interval = 6000;

LiquidCrystal_I2C lcd(0x3F, LCD_COL, LCD_ROW); //class instatiate 0x27 0x3F

void setup()
{
  // Initilize hardware serial:
  Serial.begin(9600);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
 // lcd.blink_off();  

  if (Debug == false)
  {
    drone.connect("TELLO-FE2F25", "");
  }
}

void loop()
{
  unsigned long currentdelay = millis();
  //lcd.blink_off(); 
 
  lcd.setCursor(0,0);
    

  //only send data when drone is connected to wifi
  if (drone.connected || Debug == true)
  {

    if (isCommandSent == false)
    {
      drone.sendCommand("command", Debug);

      
      if("ok" == drone.getResponse(Debug) || Debug == true)
      {
        isCommandSent = true;
      }
    }
    else
    {
           
      if ((currentdelay - previusDelayBattery) > interval)
      { 
        previusDelayBattery = currentdelay;
      
        drone.sendCommand("battery?", Debug);
        string battery = drone.getResponse(Debug);
        
        lcd.clear(); 
        lcd.setCursor(0,0);
        lcd.print("connected");
        lcd.setCursor(0,1);
        lcd.print("battery");
        lcd.setCursor(8,1);
        lcd.print(battery.c_str());
      }
      
      


      if ((MoveJoystik.getSpeedAxis(0) != 0 || MoveJoystik.getSpeedAxis(1) != 0 || rotateJoystik.getSpeedAxis(0) != 0 || rotateJoystik.getSpeedAxis(1) != 0) && (isflying == true || Debug == true))
    {
       speedx = MoveJoystik.getSpeedAxis(0);
       speedy = MoveJoystik.getSpeedAxis(1);

       int speedz = rotateJoystik.getSpeedAxis(0); 
       int speede = rotateJoystik.getSpeedAxis(1);
/*
      ostringstream s;
      s << "rc " << speedy << " " << speedx << " 0 0";
      string command = s.str();
      

     Serial.println(command.c_str());
     drone.sendCommand(command, Debug);
*/
     drone.sendRcCommand(speedy,speedx, speedz, speede, Debug) ;
    }
    else
    {
       //drone.sendCommand("stop", Debug);
    }

    if (TakeoOffButton.buttonIspressed())
    {
       Serial.println("TakeoOffButtonpressed");
       drone.sendCommand("takeoff", Debug);
      // drone.sendCommand("stop", Debug);
      isflying = true;
    }
    else
    {
      //Serial.println("NOTpressedTakeoOffButton");
    }

    if (landButton.buttonIspressed())
    {
       Serial.println("landButtonpressed");
       drone.sendCommand("land", Debug);
      // drone.sendCommand("stop", Debug);
      isflying = false;
    }
    else
    {
      //Serial.println("NOTpressedlandButton");
    }
    }    
    
  }
  else
  {
    
    lcd.setCursor(0,0);
    lcd.print("No connection");
    
  }
  
  
   
  
}