#define USE_NIMBLE

#include <Arduino.h>
#include <BleKeyboard.h>

void press_reset();
void press_up();
void press_down();
void release();
void press(uint8_t button);

const int BUTTON_RESET = 12;
const int BUTTON_UP = 13;
const int BUTTON_DOWN = 15;
const int LED_CONN = 16;
const int DELAY = 300;

const char DEVICE_NAME[12]="PAGE_TURNER";
const char DEVELOPER[5]="HLAM";

int buttonState = 0;

BleKeyboard bleKeyboard(DEVICE_NAME, DEVELOPER, 100);

void setup()
{
    pinMode(BUTTON_RESET, INPUT);
    pinMode(BUTTON_UP, INPUT);
    pinMode(BUTTON_DOWN, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LED_CONN, OUTPUT);

    Serial.begin(115200);
    Serial.println("Starting !");
    bleKeyboard.begin();
}

void loop()
{
    buttonState = 0;

    buttonState = digitalRead(BUTTON_RESET);

    if (buttonState == HIGH)
    {
        press_reset();
    }

    if (bleKeyboard.isConnected())
    {
        digitalWrite(LED_CONN, HIGH);

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
        digitalWrite(LED_CONN, LOW);
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

void press_reset()
{
    Serial.println("RESET");
    delay(DELAY);
    esp_restart();
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