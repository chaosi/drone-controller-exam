#include <Arduino.h>
#include <unity.h>
#include <Led.h>   

int pin = 16;
Led led(pin);


void test_ledlight_state_On(void)
{
    led.IsOn(true); 
    delay(500);
    TEST_ASSERT_EQUAL(digitalRead(pin), HIGH);
}

void test_ledlight_state_Off(void)
{
    led.IsOn(false);
    delay(500);
    TEST_ASSERT_EQUAL(digitalRead(pin), LOW);
}


void setup() {
   
    delay(2000);
    UNITY_BEGIN();    // Start unittesting   
    RUN_TEST(test_ledlight_state_On);
    RUN_TEST(test_ledlight_state_Off);
    pinMode(pin, OUTPUT);
    UNITY_END(); // Stop unittesting
    
}

