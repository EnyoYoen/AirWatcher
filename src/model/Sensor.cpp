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
#include <bits/stdc++.h>

Sensor &Sensor::operator=(const Sensor &unSensor)
{
    if (this != &unSensor)
    {
        this->sensorId = unSensor.sensorId;
        this->latitude = unSensor.latitude;
        this->longitude = unSensor.longitude;
        this->reliable = unSensor.reliable;
    }

    return *this;
}

Sensor::Sensor(const Sensor &unSensor)
{
    this->sensorId = unSensor.sensorId;
    this->latitude = unSensor.latitude;
    this->longitude = unSensor.longitude;
    this->reliable = unSensor.reliable;
}

Sensor::Sensor()
{
    this->sensorId = "";
    this->latitude = 0.0;
    this->longitude = 0.0;
    this->reliable = true;
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

string Sensor::toString() const
{
    stringstream ss;
    ss << sensorId << " | Lat: " << latitude << " | Lon: " << longitude << " | " << (reliable ? "Fiable" : "Non fiable");
    return ss.str();
}

string Sensor::getSensorId() const
{
    return sensorId;
}

bool Sensor::isReliable() const
{
    return reliable;
}

void Sensor::banSensor()
{
    this->reliable = false;
}

bool Sensor::checkDistance(double latitude, double longitude, double radius) const
{
    return distance(this->latitude, this->longitude, latitude, longitude) <= radius;
}

double Sensor::getDistance(double latitude, double longitude) const
{
    return distance(this->latitude, this->longitude, latitude, longitude);
}

float Sensor::calculateAirQuality(time_t startTime, time_t endTime, vector<Measurement> measurements) const
{
    float totalPM10 = 0;
    float totalNO2 = 0;
    float totalO3 = 0;
    float totalSO2 = 0;

    int countPM10 = 0;
    int countNO2 = 0;
    int countO3 = 0;
    int countSO2 = 0;

    float constPM10 = 35;
    float constNO2 = 213;
    float constO3 = 82;
    float constSO2 = 200;

    for (Measurement measurement : measurements)
    {
        if (measurement.getTimestamp() >= startTime && measurement.getTimestamp() <= endTime)
        {
            string attributeType = measurement.getAttribute();
            if (attributeType == "PM10")
            {
                totalPM10 += measurement.getValue();
                countPM10++;
            }
            else if (attributeType == "NO2")
            {
                totalNO2 += measurement.getValue();
                countNO2++;
            }
            else if (attributeType == "O3")
            {
                totalO3 += measurement.getValue();
                countO3++;
            }
            else if (attributeType == "SO2")
            {
                totalSO2 += measurement.getValue();
                countSO2++;
            }
        }
    }
    float averagePM10 = (countPM10 > 0) ? ((totalPM10 / countPM10) * 50.0 / constPM10) : 0;
    float averageNO2 = (countNO2 > 0) ? ((totalNO2 / countNO2) * 50.0 / constNO2) : 0;
    float averageO3 = (countO3 > 0) ? ((totalO3 / countO3) * 50.0 / constO3) : 0;
    float averageSO2 = (countSO2 > 0) ? ((totalSO2 / countSO2) * 50.0 / constSO2) : 0;

    return max(averagePM10, max(averageNO2, max(averageO3, averageSO2)));
}