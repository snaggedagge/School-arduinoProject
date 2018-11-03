cmake_minimum_required(VERSION 3.10)
project(Skolprojekt)

set(CMAKE_CXX_STANDARD 11)

include_directories(Canbus)
include_directories(CanBusCommon)
include_directories(ProjectLibrary)

add_executable(Skolprojekt
        Canbus/Canbus.cpp
        Canbus/Canbus.h
        Canbus/mcp2515.cpp
        Canbus/mcp2515.h
        Canbus/mcp2515_defs.h
        Canbus/MsgParsing.cpp
        Canbus/MsgParsing.h
        Canbus/VecN2KMsg.cpp
        Canbus/VecN2KMsg.h
        CanBusCommon/canbus_datamappings_defs.h
        CanBusCommon/canbus_defs.h
        CanBusCommon/canbus_error_defs.h
        CanBusCommon/canbus_global_defs.h
        CanBusCommon/canbus_id_defs.h
        CanBusCommon/canbus_struct_defs.h
        CanBusCommon/CanMessageHandler.cpp
        CanBusCommon/CanMessageHandler.h
        CanBusCommon/CanUtility.cpp
        CanBusCommon/CanUtility.h
        ProjectLibrary/Light.cpp
        ProjectLibrary/Light.h
        ProjectLibrary/TemperatureSensor.h
        ProjectLibrary/TempMsgHandler.cpp
        ProjectLibrary/TempMsgHandler.h
        temp_canbuss/temp_canbuss.ino
        wifi_canbus/wifi_canbus.ino ProjectLibrary/LightMsgHandler.h ProjectLibrary/MessageHandler.h ProjectLibrary/arduino_id_defs.h ProjectLibrary/RequestParam.h ProjectLibrary/Timer.h ProjectLibrary/HttpHandler.h)
