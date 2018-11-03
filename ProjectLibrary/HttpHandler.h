//
// Created by Dag Karlsson on 02-Nov-18.
//

#ifndef SKOLPROJEKT_HTTPHANDLER_H
#define SKOLPROJEKT_HTTPHANDLER_H

#include <cstdio>
#include <cstring>
#include "arduino_id_defs.h"

class HttpHandler {
private:
    // Ugly ass json format. Since this is arduino I will not use some heavy json formatter.
    char* jsonFormat;
    char* jsonString;

public:

    ~HttpHandler() {
        delete jsonString;
    }

    HttpHandler() {
        jsonFormat = const_cast<char *>(   "{ \n"
                                           "\"temperature\" : %lf,\n"
                                           "\n"
                                           " \"arduinos\": [\n"
                                           "    {\n"
                                           "     \"id\" : %d,\n"
                                           "     \"name\" : \"%s\",\n"
                                           "     \"lightOn\" : %s\n"
                                           "    },\n"
                                           "    {\n"
                                           "     \"id\" : %d,\n"
                                           "     \"name\" : \"%s\",\n"
                                           "     \"lightOn\" : %s\n"
                                           "    }\n"
                                           " ]\n"
                                           "} ");

        int bufferSize = strlen(jsonFormat)*4;

        jsonString = new char[bufferSize];
    }

    char* getArduinos(int recArdId, int ardId) {
        char* format = const_cast<char *>( "{ \n"
                                           " \"arduinos\": [\n"
                                           "    {\n"
                                           "     \"id\" : %d,\n"
                                           "     \"name\" : \"%s\"\n"
                                           "    },\n"
                                           "    {\n"
                                           "     \"id\" : %d,\n"
                                           "     \"name\" : \"%s\"\n"
                                           "    }\n"
                                           " ]\n"
                                           "} ");


        sprintf(jsonString, format, recArdId, ARDUINO_NAMES[recArdId], ardId, ARDUINO_NAMES[ardId]);
        return jsonString;
    }


    char* getHeader(int statusCode) {
        // memset(&arr[0], 0, sizeof(arr));
        char* contentType;
        if(statusCode == 204) {
            contentType = "Access-Control-Allow-Origin: *\n";
        }
        else {
            contentType = "Content-Type: application/json\n"
                          "Access-Control-Allow-Origin: *\n";
        }

        sprintf(jsonString, "HTTP/1.1 %d OK\n%s", statusCode, contentType);


        Serial.println(jsonString);

        return jsonString;
    }


    char* getJsonResponse(float temperature, int recArdId, bool recArdLightOn,
                                              int ardId, bool ardLightOn) {
        sprintf(this->jsonString, this->jsonFormat, temperature,
                recArdId, ARDUINO_NAMES[recArdId], recArdLightOn ? "true" : "false",
                ardId, ARDUINO_NAMES[ardId], ardLightOn ? "true" : "false");
        return this->jsonString;
    }

};


#endif //SKOLPROJEKT_HTTPHANDLER_H
