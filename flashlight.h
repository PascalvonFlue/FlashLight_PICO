#ifndef FLASHLIGHT_H
#define FLASHLIGHT_H
  #include <Arduino.h>

  #define DEBOUNCE_DELAY 50
  #define LONG_PRESS_TIME 1000
  #define DOUBLE_PRESS_TIME 800

  enum SwitchState {
    NONE,
    SHORT_PRESS,
    DOUBLE_PRESS,
    LONG_PRESS
  };

  class Falshlight_SW {
    public:
      Falshlight_SW(short pin);
      SwitchState updateSW();
    private:
      short pin;
      long debounceDelay;
      long lastDebounceTime;
      
      SwitchState state;

      bool isSwitchPressed;
      long switchPressStartTime;
      long switchPressduration;
      int lastSwitcheState = 0;
      long lastReleaseTime = 0;
      long possibleDoublePressFlag = false;
  };
#endif