// Sailingrobots libraries
#include <Canbus.h>
#include <MsgParsing.h>
#include <CanMessageHandler.h>

// Libraries created for this project
#include <LightMsgHandler.h>
#include <arduino_id_defs.h>
#include "Light.h"
#include "TempMsgHandler.h"

#define CHIP_SELECT_PIN 10

int ledHIGH    = 1;
int ledLOW     = 0;

CanbusClass Canbus;

TemperatureSensor temperatureSensor(7);
Light light(8);

TempMsgHandler temperature(&Canbus, &temperatureSensor);
LightMsgHandler lightMsgHandler(&Canbus, ARDUINO_UNO_TEMPERATURE, &light);

MessageHandler* messageHandlers[2] = {&temperature, &lightMsgHandler};

void checkCanbusFor (int timeMs){
    int startTime= millis();
    int timer = 0;
    while (timer < timeMs){
        if (Canbus.CheckForMessages()) {
            CanMsg msg;
            Canbus.GetMessage(&msg);
            for(MessageHandler* handler : messageHandlers)
                handler->notifyAboutMessage(msg);
        }
        timer = millis() - startTime;
    }
    delay(1000);
}

void setup()
{
    Serial.begin(9600);
    if(!Canbus.Init(CHIP_SELECT_PIN)) {
        Serial.println("CAN bus failed.");
    }
}

void loop()
{
    checkCanbusFor(400);
    Serial.print("Temp ");
    Serial.println(temperatureSensor.readTemperature());
}




