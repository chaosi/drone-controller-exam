#include <Arduino.h>
#include <WifiCon.h>
#include <string.h>
#include <WiFiUdp.h>
#include <Button.h>
#include <Joystick.h>
#include <Led.h>
#include <LiquidCrystal_I2C.h>

//using namespace std;

bool isCommandSent = false;
bool isflying = false;
bool canMoveMode = false;
bool debug = true;

Button TakeoOffButton(23);
Button landButton(3);
Button flightModeButton(5);
Button menuToggleLcd(4);
Joystick MoveJoystik(34,39,36,45);
Led LedGren(18);
Led LedYellow(19);
Led LedRed(16);



byte LCD_COL = 2;
byte LCD_ROW = 16;
long previusDelayBattery;
long interval = 1000;
int arrayIndex = 0;
int stepIndex = 0;

LiquidCrystal_I2C lcd(0x3F, LCD_COL, LCD_ROW); //class instatiate 0x27 0x3F
WifiCon drone("TELLO-FE2F25","", debug);

void setup()
{
  Serial.begin(9600);
  lcd.init();                     
  lcd.backlight();
  drone.connect();
  drone.setIp ("192.168.10.1");
  
}

void loop()
{
 unsigned long currentdelay = millis();
 LedGren.IsOn(canMoveMode);
 LedYellow.IsOn(!canMoveMode);
 LedRed.IsOn(!isflying);
 
 
 


  if ((currentdelay - previusDelayBattery) > interval && isCommandSent == true )
      {
        previusDelayBattery = currentdelay;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(drone.connectedStatus.c_str()); 
        lcd.setCursor(0,1);
        lcd.print(drone.telemetry[arrayIndex].c_str());       
      }
      else
      {
        
        lcd.setCursor(0,0);
        lcd.print(drone.connectedStatus.c_str()); 
      }
      
     
    
  
  
  //only send data when drone is connected to wifi
  if (drone.connected || debug == true)
  {       
    if (isCommandSent == false)
    {
      drone.sendCommand("command");
      string rdy = drone.getResponse(); 
      if(rdy == "ok")
      {
        isCommandSent = true;
        lcd.clear();        
        lcd.setCursor(0,0);
        lcd.print("ready");
        Serial.println("ready");      
      }      
    }
    else if(isCommandSent == true)
    {   

      if (menuToggleLcd.buttonIspressed())// cycle arrayIndex int
      {
        if (arrayIndex >= 2)
        {
          arrayIndex = 0;
        }
        else
        {
          arrayIndex++;
        }                     
        Serial.println(arrayIndex);
      }
   
      if ((MoveJoystik.getSpeedAxisX() != 0 || MoveJoystik.getSpeedAxisY() != 0) && isflying == true)// check if ps2 joystick is pushed
      {
       
        if (canMoveMode == true) //send rc command input based on flightmode
        {
          drone.sendRcCommand(MoveJoystik.getSpeedAxisX(),MoveJoystik.getSpeedAxisY(),0,0);
        }
        else
        {
          drone.sendRcCommand(0,0,MoveJoystik.getSpeedAxisX(),MoveJoystik.getSpeedAxisY());
        }
      }
      else if(isflying == true)// if no ps2 joystick is detected send Rc command with 0 values to keep drone in place
      {
         drone.sendCommand("rc 0 0 0 0");
      }


      if (flightModeButton.buttonIspressed())
        {
          Serial.println("flightModeButton");
          canMoveMode = !canMoveMode;
        }
      
   
      if (landButton.buttonIspressed())
        {
           drone.sendCommand("land");
          isflying = false;
        }

      if (TakeoOffButton.buttonIspressed())
        {
          drone.sendCommand("takeoff");
          isflying = true;
        }
    }
  }
  else
  {     
    isCommandSent = false;      
  }  
}