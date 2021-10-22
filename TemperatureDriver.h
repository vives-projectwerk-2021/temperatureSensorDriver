#pragma once

#include "stdint.h"

class TemperatureSensorMoisture
{
    public:
        TemperatureSensor();
        float temperature();

        
    private: 
        static const int CONFIG = 0x01;
        static const int TsetLimit = 0x11;
        static const char ReadTemp = 0x00;
};

class TemperatureSensorMain
{
    public:
        TemperatureSensor();
        float temperature();
    private: 
        static const int CONFIG = 0x01;
        static const int TsetLimit = 0x11;
        static const char ReadTemp = 0x00;
        
};