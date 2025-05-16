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

float Sensor::calculateAirQuality(time_t startTime, time_t endTime, List<Measurement> measurements)
{
    float totalPM10 = 0;
    float totalNO2 = 0;
    float totalO3 = 0;
    float totalSO2 = 0;

    int countPM10 = 0;
    int countNO2 = 0;
    int countO3 = 0;
    int countSO2 = 0;

    for (Measurement measurement : measurements)
    {
        if (measurement.getTime() >= startTime && measurement.getTimestamp() <= endTime)
        {
            string attributeType = measurement.getAttribute();
            switch (attributeType)
            {
            case "PM10":
                totalPM10 += measurement.getValue();
                break;

            case "NO2":
                totalNO2 += measurement.getValue();
                break;

            case "O3":
                totalO3 += measurement.getValue();
                break;

            case "SO2":
                totalSO2 += measurement.getValue();
                break;

            default:
                break;
            }
        }
    }
    float averagePM10 = (countPM10 > 0) ? ((totalPM10 / countPM10) * 50 / 35) : 0;
    float averageNO2 = (countNO2 > 0) ? ((totalNO2 / countNO2) * 50 / 213) : 0;
    float averageO3 = (countO3 > 0) ? ((totalO3 / countO3) * 50 / 82) : 0;
    float averageSO2 = (countSO2 > 0) ? ((totalSO2 / countSO2) * 50 / 200) : 0;

    return max(averagePM10, max(averageNO2, max(averageO3, averageSO2)));
}
{
}