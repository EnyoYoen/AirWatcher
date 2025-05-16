/*************************************************************************
                           Sensor  -  description
                             -------------------
    début                : 16/5/2025
    copyright            : (C) 2025 par Garoux, Hequet, McCurdy, Lafon de la Laurencie, Peyrot.
*************************************************************************/

#if ! defined ( SENSOR_H )
#define SENSOR_H

class Sensor
{

public:
    Sensor & operator = ( const Sensor & unSensor );


    Sensor ( const Sensor & unSensor );
    Sensor ( string sensorId, double latitude, double longitude);
    virtual ~Sensor ( );

    
    void banSensor ( );
    bool checkDistance ( double latitude, double longitude, double radius );

protected:
    string sensorId;
    double latitude;
    double longitude;
    bool reliable;
};

#endif // SENSOR_H

