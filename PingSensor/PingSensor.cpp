/**
 * PingSensor.cpp - Library for controlling ping sensors.
 * Author: Kevin Barnfield
 * Date: March 24, 2018
 */

#include "Arduino.h"
#include "PingSensor.h"

PingSensor::PingSensor(int trig, int echo)
{
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);

    this->trig = trig;
    this->echo = echo;

    // Smoothing
    readIndex = 0;
    total = 0;
    average = 0;
    for (int i = 0; i < numReadings; i++) {
        readings[i] = 0
    }
}

int PingSensor::getDist()
{
    digitalWrite(trig, LOW);
    delayMicroseconds(2);

    digitalWrite(trig, HIGH);
    delayMicroseconds(10);

    digitalWrite(trig, LOW);
    int duration = pulseIn(echo, HIGH);

    // Calculate distance (in cm) based on speed of sound
    int distance = duration / 58.2;

    // Smoothing (Optional but recommended)
    // Subtract previous reading
    total = total - readings[readIndex];
    // Read from the sensors
    readings[readIndex] = distance;
    // Add the reading to the total
    total = total + readings[readIndex];
    // Advance to the next position
    readIndex = readIndex + 1;

    // If at end of array, wrap back
    if (readIndex >= numReadings) {
        readIndex = 0;
    }

    // Return the average
    return total / numReadings;
}
