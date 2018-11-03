//
// Created by Dag Karlsson on 02-Nov-18.
//

#ifndef SKOLPROJEKT_REQUESTPARAM_H
#define SKOLPROJEKT_REQUESTPARAM_H


#include <WString.h>

class RequestParam {
public:
    String name;
    String value;
};

class RequestParamParser {
private:
    RequestParam* requestParams;
    int paramSize;

    int lastParamIndex = 0;

public:
    RequestParamParser(int paramSize = 5) {
        this->requestParams = new RequestParam[paramSize];
        this->paramSize = paramSize;
    }

    ~RequestParamParser(){
        delete requestParams;
    }


    void parseRequest(String request) {
        String requestParams = request.substring((unsigned int) request.indexOf("?") + 1);
        requestParams = requestParams.substring(0,(unsigned int) requestParams.indexOf(' '));

        // Easy scalable
        String paramString[2];

        int counter = 0;
        do {
            String param = requestParams;

            int paramEndIndex = requestParams.indexOf("&");
            if (paramEndIndex != -1) {
                param = requestParams.substring(0, (unsigned int) paramEndIndex);
                requestParams = requestParams.substring((unsigned int) paramEndIndex +1, requestParams.length());
                paramString[counter++] = param;
            }
        } while(requestParams.indexOf('&') != -1  && counter < paramSize);
        lastParamIndex = counter;

        if(requestParams.indexOf("&") == -1) {
            paramString[counter] = requestParams;
        }

        for(int i=0; i < sizeof(paramString) / sizeof(String); i++) {
            String param = paramString[i];
            this->requestParams[i].name = param.substring(0, (unsigned int) param.indexOf("="));
            this->requestParams[i].value = param.substring((unsigned int)param.indexOf("=")+1);
        }
    }

    int getNrOfParameters() {
        return lastParamIndex+1;
    }

    RequestParam getParam(int index) {
        return this->requestParams[index];
    }

};



#endif //SKOLPROJEKT_REQUESTPARAM_H
