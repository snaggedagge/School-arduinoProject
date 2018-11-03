//
// Created by Dag Karlsson on 01-Nov-18.
//

#ifndef SKOLPROJEKT_TEMPERATUREMESSAGE_H
#define SKOLPROJEKT_TEMPERATUREMESSAGE_H


#include <Canbus.h>
#include "TemperatureSensor.h"
#include "MessageHandler.h"

#define MESSAGE_TEMPERATURE_REQUEST 5
#define MESSAGE_TEMPERATURE_RESPONSE 10

#define TEMPERATURE_DATA_SIZE 4

#define TEMPERATURE_DATA_LOWER_LIMIT (-20)
#define TEMPERATURE_DATA_UPPER_LIMIT 30


class TempMsgHandler : public MessageHandler {
private:
    CanbusClass* canbus;
    float temperature;
    TemperatureSensor* temperatureInterface;
public:
    explicit TempMsgHandler(CanbusClass* canbus, TemperatureSensor* temperatureInterface = nullptr);

    bool notifyAboutMessage(CanMsg canMsg) override;

    float getTemperature();
};




#endif //SKOLPROJEKT_TEMPERATUREMESSAGE_H
