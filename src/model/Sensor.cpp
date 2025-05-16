/*************************************************************************
                           Sensor  -  description
                             -------------------
    début                : 16/5/2025
    copyright            : (C) 2025 par Garoux, Hequet, McCurdy, Lafon de la Laurencie, Peyrot.
*************************************************************************/

using namespace std;

#include <iostream>

#include "Sensor.h"
#include "../utils/GPS.h"

Sensor &Sensor::operator=(const Sensor &unSensor)
{
    if (this != &unSensor)
    {
        this->sensorId = unSensor.sensorId;
        this->latitude = unSensor.latitude;
        this->longitude = unSensor.longitude;
        this->reliable = unSensor.reliable;
    }
}

Sensor::Sensor(const Sensor &unSensor)
{
    this->sensorId = unSensor.sensorId;
    this->latitude = unSensor.latitude;
    this->longitude = unSensor.longitude;
    this->reliable = unSensor.reliable;
}

Sensor::Sensor(string sensorId, double latitude, double longitude)
{
    this->sensorId = sensorId;
    this->latitude = latitude;
    this->longitude = longitude;
    this->reliable = true;
}

Sensor::~Sensor()
{
}

void Sensor::banSensor()
{
    this->reliable = false;
}

bool Sensor::checkDistance(double latitude, double longitude, double radius)
{
    return distance(this->latitude, this->longitude, latitude, longitude) <= radius;
}