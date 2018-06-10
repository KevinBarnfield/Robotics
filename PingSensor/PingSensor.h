/**
 * PingSensor.h - Library for controlling ping sensors.
 * Author: Kevin Barnfield
 * Date: March 24, 2018
 */

#ifndef PING_H
#define PING_H

#include "Arduino.h"

class PingSensor
{
    public:
        static const int max = 200;
        static const int min = 0;

        PingSensor(int trig, int echo);
        int getDist();
    private:
        int trig;
        int echo;

        // Smoothing Variables
        const int numReadings = 10;
        int readings[numReadings];
        int readIndex;
        int total;
};

#endif
