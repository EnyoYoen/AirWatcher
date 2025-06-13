/*************************************************************************
                           Sensor  -  description
                             -------------------
    début                : 16/5/2025
    copyright            : (C) 2025 par Garoux, Hequet, McCurdy, Lafon de la Laurencie, Peyrot.
*************************************************************************/

#if !defined(SENSOR_H)
#define SENSOR_H

#include <ctime>
#include <string>
#include <vector>

#include "Measurement.h"
#include "../utils/GPS.h"

class Sensor
{

public:
    Sensor &operator=(const Sensor &unSensor);

    Sensor(const Sensor &unSensor);
    Sensor();
    Sensor(string sensorId, double latitude, double longitude);
    virtual ~Sensor();

    string toString() const;
    string getSensorId() const;
    bool isReliable() const;

    void banSensor();
    bool checkDistance(double latitude, double longitude, double radius) const;
    double getDistance(double latitude, double longitude) const;
    float calculateAirQuality(time_t startTime, time_t endTime, vector<Measurement> measurements) const;

protected:
    string sensorId;
    double latitude;
    double longitude;
    bool reliable;
};

#endif // SENSOR_H
