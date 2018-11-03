//
// Created by Dag Karlsson on 01-Nov-18.
//
#include <Arduino.h>
#include <CanMessageHandler.h>
#include "TempMsgHandler.h"

TempMsgHandler::TempMsgHandler(CanbusClass *canbus, TemperatureSensor* temperatureInterface) {
    this->canbus = canbus;
    this->temperatureInterface = temperatureInterface;
    this->temperature=0;
}

float TempMsgHandler::getTemperature() {
    CanMessageHandler requestMessage(MESSAGE_TEMPERATURE_REQUEST);
    canbus->SendMessage(requestMessage.getMessage());
    return temperature;
}

bool TempMsgHandler::notifyAboutMessage(CanMsg canMsg) {

    CanMessageHandler message(canMsg);
    if(message.getMessageId() == MESSAGE_TEMPERATURE_REQUEST) {
        // Just in case
        if (temperatureInterface == nullptr) {
            Serial.println("Temperature interface is null");
            return false;
        }

        CanMessageHandler returnMessage(MESSAGE_TEMPERATURE_RESPONSE);
        returnMessage.encodeMappedMessage(TEMPERATURE_DATA_SIZE,temperatureInterface->readTemperature(), TEMPERATURE_DATA_LOWER_LIMIT, TEMPERATURE_DATA_UPPER_LIMIT);
        canbus->SendMessage(returnMessage.getMessage());
        return true;
    }
    else if(message.getMessageId() == MESSAGE_TEMPERATURE_RESPONSE) {
        message.getMappedData(&temperature, TEMPERATURE_DATA_SIZE, TEMPERATURE_DATA_LOWER_LIMIT, TEMPERATURE_DATA_UPPER_LIMIT);
    }

    return false;
}
