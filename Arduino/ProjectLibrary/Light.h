//
// Created by Dag Karlsson on 01-Nov-18.
//

#ifndef SKOLPROJEKT_LIGHT_H
#define SKOLPROJEKT_LIGHT_H


class Light {
private:
    bool isLightsOn = false;
    int gpioPin;
public:
    Light(int pin);

    void turnLightOn(bool turnLightOn);
    bool isLightOn();
};


#endif //SKOLPROJEKT_LIGHT_H
