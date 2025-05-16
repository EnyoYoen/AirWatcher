/*************************************************************************
                           Sensor  -  description
                             -------------------
    début                : 16/5/2025
    copyright            : (C) 2025 par Garoux, Hequet, McCurdy, Lafon de la Laurencie, Peyrot.
*************************************************************************/

using namespace std;

#include <iostream>
#include <cmath>

#include "Sensor.h"

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

double Sensor::distance(double lat1, double lon1, double lat2, double lon2)
{
    // Haversine formula to calculate the distance between two points on the Earth
    const double R = 6371.0;
    double dLat = toRadians(lat2 - lat1);
    double dLon = toRadians(lon2 - lon1);
    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(toRadians(lat1)) * cos(toRadians(lat2)) *
                   sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return R * c;
}

double Sensor::toRadians(double degree)
{
    return degree * M_PI / 180.0;
}