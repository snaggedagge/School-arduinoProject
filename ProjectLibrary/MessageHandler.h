//
// Created by Dag Karlsson on 01-Nov-18.
//

#ifndef SKOLPROJEKT_MESSAGEHANDLER_H
#define SKOLPROJEKT_MESSAGEHANDLER_H


#include <canbus_defs.h>

class MessageHandler {
public:
    virtual bool notifyAboutMessage(CanMsg canMsg) = 0;
};


#endif //SKOLPROJEKT_MESSAGEHANDLER_H
