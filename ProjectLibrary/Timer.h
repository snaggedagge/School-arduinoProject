//
// Created by Dag Karlsson on 02-Nov-18.
//

#ifndef SKOLPROJEKT_TIMER_H
#define SKOLPROJEKT_TIMER_H


class Timer {
private:
    long startTime=0;

public:
    bool hasTimePassed(int milliseconds) {
        return (startTime + milliseconds < millis());
    }

    void reset() {
        startTime = millis();
    }
};


#endif //SKOLPROJEKT_TIMER_H
