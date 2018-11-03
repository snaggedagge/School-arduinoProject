
// Arduino libraries
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include <ESP8266WebServer.h>

// Sailingrobots libraries
#include <Canbus.h>
#include <MsgParsing.h>
#include <CanMessageHandler.h>

// Libraries created for this project
#include <LightMsgHandler.h>
#include <arduino_id_defs.h>
#include <RequestParam.h>
#include <Timer.h>
#include <functional>
#include <HttpHandler.h>
#include "Light.h"
#include "TempMsgHandler.h"

#define CHIP_SELECT_PIN 15

CanbusClass Canbus;


const char *ssid = "Arduino";
const char *password = "test";

/*
const char *ssid = "4G-Gateway-21E0";
//const char *ssid = "OnePlus6";
const char *password = "snaggedagge";


IPAddress ipAdress(192,168,1,50);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
WiFiServer server(80);
 */

ESP8266WebServer server(80);

HttpHandler httpHandler;

Timer tempTimer;
Timer canbusTimer;

Light light(2);

TempMsgHandler tempMsgHandler(&Canbus);
LightMsgHandler lightMsgHandler(&Canbus, NODE_MCU_WIFI, &light);

RequestParamParser paramParser;

float temperature = 0;

void checkCanbus (int timeMs){
    canbusTimer.reset();
    while (!canbusTimer.hasTimePassed(400)){
        if (Canbus.CheckForMessages()) {
            CanMsg msg;
            Canbus.GetMessage(&msg);
            tempMsgHandler.notifyAboutMessage(msg);
            lightMsgHandler.notifyAboutMessage(msg);
        }
    }
}


/*
void checkWifi() {
    WiFiClient client;
    if((client = server.available()) && client.available()) {
        String request = client.readStringUntil('\r');
        paramParser.parseRequest(request);
        client.flush();
        Serial.println("Starting printing");
        if (request.indexOf("/lights") != -1) {
            for(int i=0; i < paramParser.getNrOfParameters(); i++) {
                RequestParam param = paramParser.getParam(i);

                int arduinoId = param.name.toInt();
                bool turnLightOn = param.value.equals("true");
                lightMsgHandler.setArduinoLight((uint8_t)arduinoId, turnLightOn);
            }
            client.println(httpHandler.getHeader(204));
        }
        else if(request.indexOf("/arduinos") != -1) {
            client.println(httpHandler.getHeader(200));
            client.println(httpHandler.getArduinos(lightMsgHandler.getRecieverArduinoId(), lightMsgHandler.getArduinoId()));
        }
        else if(request.indexOf("/status") != -1) {
            client.println(httpHandler.getHeader(200));

            char* jsonResponse = httpHandler.getJsonResponse(temperature, lightMsgHandler.getRecieverArduinoId(), lightMsgHandler.isRecieverLightOn(),
                                                             lightMsgHandler.getArduinoId(), lightMsgHandler.isLightOn());
            client.println(jsonResponse);
        }
        //client.stop();
        Serial.println("Ending printing");
    }
}

 */

/*
void setup() {
     Serial.begin(9600);
    if(!Canbus.Init(CHIP_SELECT_PIN)) {
        Serial.println("CAN bus failed.");
    }
    //WiFi.config(ipAdress,gateway,subnet);
    WiFi.begin(ssid, password);

    Serial.print("Connecting to wifi ");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.print("\nIP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
    lightMsgHandler.setArduinoLight(ARDUINO_UNO_TEMPERATURE, false);
}
 */

void handleRoot() {
    server.send(200, "text/html", "<h1>You are connected</h1>");
}

void setup() {
    Serial.begin(9600);
    if(!Canbus.Init(CHIP_SELECT_PIN)) {
        Serial.println("CAN bus failed.");
    }
    WiFi.softAP(ssid);

    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    server.on("/", handleRoot);
    server.begin();
    Serial.println("HTTP server started");

    lightMsgHandler.setArduinoLight(ARDUINO_UNO_TEMPERATURE, false);
}

void loop() {
    if( tempTimer.hasTimePassed(2000)) {
        tempTimer.reset();
        temperature = tempMsgHandler.getTemperature();
    }

    server.handleClient();
    //checkWifi();
    checkCanbus(200);
}






