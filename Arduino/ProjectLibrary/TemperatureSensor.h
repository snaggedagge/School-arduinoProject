//
// Created by Dag Karlsson on 01-Nov-18.
//

#ifndef SKOLPROJEKT_TEMPERATUREINTERFACE_H
#define SKOLPROJEKT_TEMPERATUREINTERFACE_H

#include "DHT.h"

#define DHTTYPE DHT22   // DHT 22  (AM2302)

class TemperatureSensor {
private:
    DHT* dht;

    float temperature = 0;
public:
    TemperatureSensor(int dhtPin) {
        this->dht = new DHT(dhtPin, DHTTYPE);
        this->dht->begin();
    }

    float readTemperature() {
        return dht->readTemperature();
    }
};

#endif //SKOLPROJEKT_TEMPERATUREINTERFACE_H
