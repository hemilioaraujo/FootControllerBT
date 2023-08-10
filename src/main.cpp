#define USE_NIMBLE

#include <Arduino.h>
#include <BleKeyboard.h>

void press_up();
void press_down();
void release();
void press(uint8_t button);

const int BUTTON_UP = 13;
const int BUTTON_DOWN = 15;
const int DELAY = 300;

int buttonState = 0;

BleKeyboard bleKeyboard("PAGE_TURNER", "HLAM", 100);

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(BUTTON_UP, INPUT);
    pinMode(BUTTON_DOWN, INPUT);
    Serial.begin(115200);
    Serial.println("Starting BLE work!");
    bleKeyboard.begin();
}

void loop()
{
    buttonState = 0;

    if (bleKeyboard.isConnected())
    {
        digitalWrite(LED_BUILTIN, LOW);

        buttonState = digitalRead(BUTTON_UP);

        if (buttonState == HIGH)
        {
            press_up();
        }

        buttonState = digitalRead(BUTTON_DOWN);

        if (buttonState == HIGH)
        {
            press_down();
        }
    }
    else
    {
        digitalWrite(LED_BUILTIN, HIGH);
    }
}

void press_up()
{
    Serial.println("UP");
    press(KEY_UP_ARROW);
}

void press_down()
{
    Serial.println("DOWN");
    press(KEY_DOWN_ARROW);
}

void release()
{
    bleKeyboard.releaseAll();
    delay(DELAY);
}

void press(uint8_t button)
{
    bleKeyboard.press(button);
    delay(DELAY);
    release();
}