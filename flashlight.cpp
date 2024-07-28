#include "flashlight.h"



Falshlight_SW::Falshlight_SW(short pin):
pin(pin), debounceDelay(DEBOUNCE_DELAY), lastDebounceTime(0), state(NONE), isSwitchPressed(false){

}

SwitchState Falshlight_SW::updateSW() {
    int readSwitch = digitalRead(pin);
    unsigned long currentTime = millis();

    // Check if the button state has changed, if changed reset the debounce time
    if (readSwitch != lastSwitcheState) {
        lastDebounceTime = currentTime;
    }

    // Debounce the button change
    if ((currentTime - lastDebounceTime) > debounceDelay) {
        if (readSwitch == LOW) {
            // Button is still pressed after the debounce
            if (!isSwitchPressed) {
                //Register the button press
                switchPressStartTime = currentTime;
                isSwitchPressed = true;
                state = NONE;
            } else {
                // check how long the button was pressed
                switchPressduration = currentTime - switchPressStartTime;
                if (switchPressduration > LONG_PRESS_TIME && state == NONE) {
                    //Serial.println("Long press");
                    state = LONG_PRESS;
                    switchPressduration = 0;
                }
            }
        } else if (readSwitch == HIGH && isSwitchPressed) {
            // Button is not pressed anymore, but previously the button was pressed, but also not long enough for a longpress
            // Short press opens the possibility for a double press
            if (state == NONE) {
              if(possibleDoublePressFlag && (currentTime - lastReleaseTime < DOUBLE_PRESS_TIME)){
                //Serial.println("Double press");
                state = DOUBLE_PRESS;
                possibleDoublePressFlag = false;
              } else {
                //Serial.println("Short press");
                state = SHORT_PRESS;
                lastReleaseTime = currentTime;
                possibleDoublePressFlag = true;
              }
            }
            isSwitchPressed = false;
        }
    }

    // Reset the possibility for a doublepress when out of the timewondow
    if (possibleDoublePressFlag && (currentTime - lastReleaseTime > DOUBLE_PRESS_TIME)) {
        possibleDoublePressFlag = false;
    }

    lastSwitcheState = readSwitch;
    return state;
}