#include <unity.h>
#include <Button.h>

int pin = 2;
Button button(pin);


void test_Button_Pin(void) {
    TEST_ASSERT_EQUAL(2, pin);
}

void test_Button_state_pressed(void)
{
    digitalWrite(pin, HIGH);    
    delay(500);
    TEST_ASSERT_EQUAL(button.buttonIspressed(), true);
}


void test_Button_state_pressed_Not(void)
{
    digitalWrite(pin, LOW);   
    delay(500);
    TEST_ASSERT_EQUAL(button.buttonIspressed(), false);
}


void setup() {
   
    delay(2000);
    pinMode(pin, INPUT_PULLUP);
    UNITY_BEGIN();    // Start unittesting
    RUN_TEST(test_Button_state_pressed);
    RUN_TEST(test_Button_state_pressed_Not);
    RUN_TEST(test_Button_Pin);
    UNITY_END(); // Stop unittesting
    
}

void loop()
{
    
}