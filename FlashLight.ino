/************************ Hardware Setup **************************/
//                    GPIO 19 -> R330 -> GND
//                        GPIO 10 -> GND
/******************************************************************/

#include "flashlight.h"

#define LED_PWM 19
#define SW_PIN 10

Falshlight_SW lightSW(SW_PIN);

void setup() {
  Serial.begin(9600);
  pinMode(LED_PWM, OUTPUT);
  pinMode(SW_PIN, INPUT_PULLUP);
}

void loop() {
  SwitchState cstate = lightSW.updateSW();
  switch (cstate) {
    case SHORT_PRESS:
      //Serial.println("Short press");
      analogWrite(LED_PWM, 50);
      break;
    case DOUBLE_PRESS:
      //Serial.println("Double press");
      analogWrite(LED_PWM, 0);
      break;
    case LONG_PRESS:
      //Serial.println("Long press");
      analogWrite(LED_PWM, 255);
      break;
    default:
      break;
  }

  //delay(100);
  
}
