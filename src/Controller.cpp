#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Controller.h>

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

uint8_t bell[8]  = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4};
uint8_t note[8]  = {0x2,0x3,0x2,0xe,0x1e,0xc,0x0};
uint8_t heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};
uint8_t duck[8]  = {0x0,0xc,0x1d,0xf,0xf,0x6,0x0};
uint8_t check[8] = {0x0,0x1,0x3,0x16,0x1c,0x8,0x0};
uint8_t cross[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};
uint8_t retarrow[8] = {	0x1,0x1,0x5,0x9,0x1f,0x8,0x4};
  

//byte LCD_COL = 2;
//byte LCD_ROW = 16;

//LiquidCrystal_I2C lcd(0x3F, 2, 16); //class instatiate 0x27 0x3F

Controller::Controller( )
    {
        // this->LCD_COL =LCD_COL;
        // this->LCD_ROW = LCD_ROW;
        init();
    } 

    void Controller::init()
    {
    //lcd.init();                      // initialize the lcd 
    //lcd.backlight();  
    /*
    lcd.createChar(0, bell);
    lcd.createChar(1, note);
    lcd.createChar(3, heart);
    lcd.createChar(4, duck);
    lcd.createChar(5, check);
    lcd.createChar(6, cross);
    lcd.createChar(7, retarrow);
    lcd.home();
    */
    //lcd.print("Hello world...");
    //lcd.setCursor(0, 1);
    //lcd.print(" i ");
    //lcd.printByte(3);
    //lcd.print(" arduinos!");   
    }


    void Controller::Write(String text,int row, int col)
    {
    //lcd.setCursor(col,row);
    //lcd.print(text);
    }

    void Controller::clear()
    {
     //lcd.clear();
    }
