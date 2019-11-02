#ifndef Controller_h
#define Controller_h
#include <string>
#include <LiquidCrystal_I2C.h>
using namespace std;

 class Controller
{

    private:
     

    public:      
       Controller();
       void init();
      void Write(String text,int row, int col);
       void clear();
        
        

        
};

#endif