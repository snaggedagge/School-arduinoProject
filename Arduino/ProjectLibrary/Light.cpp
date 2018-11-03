//
// Created by Dag Karlsson on 01-Nov-18.
//

#include <Arduino.h>
#include "Light.h"

Light::Light(int pin) {
    pinMode(pin, OUTPUT);
    digitalWrite(gpioPin, HIGH);
    gpioPin = pin;
}

bool Light::isLightOn() {
    return isLightsOn;
}

void Light::turnLightOn(bool turnLightOn) {
    if (turnLightOn)  {
        digitalWrite(gpioPin, LOW);
    }
    else {
        digitalWrite(gpioPin, HIGH);
    }
    isLightsOn = turnLightOn;
}



