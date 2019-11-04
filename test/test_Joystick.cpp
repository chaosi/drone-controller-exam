#include <Arduino.h>
#include <unity.h>
#include <Joystick.h>

int pin_sw = 2;
int pin_X = 2;
int pin_Y = 2;
int DeadZone = 40;

Joystick joystick(pin_sw,pin_X,pin_Y,DeadZone);



void test_JButton_state_pressed(void)
{
    digitalWrite(pin_sw, HIGH);    
    delay(500);   
    TEST_ASSERT_EQUAL(joystick.buttonIspressed(), true);
}


void test_JButton_state_pressed_Not(void)
{

     digitalWrite(pin_sw, LOW);   
    delay(500);
    TEST_ASSERT_EQUAL(joystick.buttonIspressed(), false);
}

void test_X_axis_Max(void)
{
    //analogWrite(pin_X, 4095);/// analog write dosnt seem to work firmware issue (https://github.com/espressif/arduino-esp32/issues/4)
    digitalWrite(pin_X, HIGH);      
    delay(500);
    TEST_ASSERT_EQUAL(joystick.getSpeedAxisX(), 100);   
}

void test_X_axis_Min(void)
{   
    //analogWrite(pin_X, 0);/// analog write dosnt seem to work firmware issue (https://github.com/espressif/arduino-esp32/issues/4)
    digitalWrite(pin_X, LOW);      
    delay(500);
    TEST_ASSERT_EQUAL(joystick.getSpeedAxisX(), -100);   
}

void test_Y_axis_Max(void) /// analog write dosnt seem to work firmware issue (https://github.com/espressif/arduino-esp32/issues/4)
{
    //analogWrite(pin_Y, 4095);
    digitalWrite(pin_Y, HIGH);      
    delay(500);
    TEST_ASSERT_EQUAL(joystick.getSpeedAxisY(), -100);   
}

void test_Y_axis_Min(void) /// analog write dosnt seem to work firmware issue (https://github.com/espressif/arduino-esp32/issues/4)
{
    //analogWrite(pin_Y, 0);
    digitalWrite(pin_Y, LOW);      
    delay(500);
    TEST_ASSERT_EQUAL(joystick.getSpeedAxisY(), 100);   
}


void setup() {
   
    delay(2000);
    UNITY_BEGIN();    // Start unittesting
    RUN_TEST(test_JButton_state_pressed);
    RUN_TEST(test_JButton_state_pressed_Not);
    RUN_TEST(test_X_axis_Max);
    RUN_TEST(test_X_axis_Min);
    RUN_TEST(test_Y_axis_Max);
    RUN_TEST(test_Y_axis_Min);
    UNITY_END(); // Stop unittesting
    
}

