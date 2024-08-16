

#ifndef MILLIAMP_CONV_HPP
#define MILLIAMP_CONV_HPP

#include <Arduino.h>
#include "EVENTS.hpp"
#include "variable_init.hpp"

#define minADCValue  1023  // Approximate value for 4mA
#define maxADCValue  4095  // Approximate value for 20mA

class MilliAmp_Conv
{
public:
    float current_mA();
    float voltage_V();

// private:
//     float CONV_CURRENT_V14;
//     float CONV_VOLTAGE_V14;
};

#endif // MILLIAMP_CONV_HPP