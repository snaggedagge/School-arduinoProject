//
// Created by Dag Karlsson on 01-Nov-18.
//

#ifndef SKOLPROJEKT_LIGHTMSGHANDLER_H
#define SKOLPROJEKT_LIGHTMSGHANDLER_H


#include <CanMessageHandler.h>
#include <Canbus.h>
#include "MessageHandler.h"
#include "Light.h"

#define MESSAGE_LIGHT_REQUEST 20
#define MESSAGE_LIGHT_RESPONSE 25

#define LIGHT_ARDUINO_ID_SIZE 1
#define LIGHT_LIGHTS_ON_SIZE 1


class LightMsgHandler: public MessageHandler{
private:
    uint8_t arduinoId;
    CanbusClass* canbus;
    Light* light;

    uint8_t recieverArduinoId=0;
    bool recieverLightOn=false;
public:
    explicit LightMsgHandler(CanbusClass* canbus, uint8_t arduinoId = 0, Light* light = nullptr) {
        this->canbus = canbus;
        this->arduinoId = arduinoId;
        this->light = light;
    }

    bool notifyAboutMessage(CanMsg canMsg) override {
        CanMessageHandler messageHandler(canMsg);

        if(messageHandler.getMessageId() == MESSAGE_LIGHT_REQUEST) {
            uint8_t targetArduino;
            uint8_t turnLightOn;
            messageHandler.getData(&targetArduino, LIGHT_ARDUINO_ID_SIZE);
            messageHandler.getData(&turnLightOn, LIGHT_LIGHTS_ON_SIZE);

            if(targetArduino == this->arduinoId) {
                light->turnLightOn((bool) turnLightOn);
                CanMessageHandler responseHandler(MESSAGE_LIGHT_RESPONSE);
                responseHandler.encodeMessage(LIGHT_ARDUINO_ID_SIZE, arduinoId);
                responseHandler.encodeMessage(LIGHT_LIGHTS_ON_SIZE, (uint8_t)light->isLightOn());
                canbus->SendMessage(responseHandler.getMessage());
            }
        }
        if(messageHandler.getMessageId() == MESSAGE_LIGHT_RESPONSE) {
            uint8_t recieverArduinoId;
            uint8_t recieverLightOn;
            messageHandler.getData(&recieverArduinoId, LIGHT_ARDUINO_ID_SIZE);
            messageHandler.getData(&recieverLightOn, LIGHT_LIGHTS_ON_SIZE);
            this->recieverLightOn = recieverLightOn;
            this->recieverArduinoId = recieverArduinoId;
        }
    }

    void setArduinoLight(uint8_t arduinoId, bool turnLightOn) {

        if(arduinoId == this->arduinoId) {
            this->light->turnLightOn(turnLightOn);
            return;
        }

        CanMessageHandler request(MESSAGE_LIGHT_REQUEST);

        request.encodeMessage(LIGHT_ARDUINO_ID_SIZE, arduinoId);
        request.encodeMessage(LIGHT_LIGHTS_ON_SIZE, (uint8_t)turnLightOn);
        canbus->SendMessage(request.getMessage());
    }

    bool isRecieverLightOn() {
        return recieverLightOn;
    }

    uint8_t getRecieverArduinoId() {
        return recieverArduinoId;
    }

    bool isLightOn() {
        return light->isLightOn();
    }

    uint8_t getArduinoId() {
        return arduinoId;
    }

};


#endif //SKOLPROJEKT_LIGHTMSGHANDLER_H
