/*************************************************************************
                           AirWatcher  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <AirWatcher> (fichier AirWatcher.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "AirWatcher.h"

#include "../utils/DataLoader.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type AirWatcher::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

list<Sensor> findSimilarSensors(long sensorId);

float AirWatcher::calculateAirQuality(time_t startTime, time_t endTime, double radius, double latitude, double longitude)
{
    float averageAQI = 0;
    int count = 0;
    for (Sensor sensor : sensorslist)
    {
        if (sensor.checkDistance(latitude, longitude, radius))
        {
            // Assuming Sensor has a method to get air quality
            float airQuality = sensor.calculateAirQuality(startTime, endTime, measurements[sensor.getSensorId()]);
            if (airQuality > 0)
            {
                averageAQI += airQuality;
                count++;
            }
        }
    }
    return (count > 0) ? (averageAQI / count) : -1;
}

bool AirWatcher::checkMalfunction(long sensorId)
{
    // TODO
    return false;
}

float AirWatcher::pointAirQuality(double latitude, double longitude, time_t time)
{
    // TODO
    return 0.0;
}

float AirWatcher::measureCleanerImpact(long cleanerId)
{
    // TODO
    return 0.0;
}

bool AirWatcher::checkUnreliableSensor(long sensorId, long userId)
{
    // TODO
    return false;
}

void AirWatcher::awardPoints(long userId)
{
    // TODO
}

Bool AirWatcher::loadData()
{
    DataLoader::loadSensors(sensorsList);
    DataLoader::loadMeasurements(measurements, attributes);
    DataLoader::loadUsers(usersList);
    DataLoader::loadProviders(providersList);
}

User AirWatcher::login(long userId, string password)
{
    // TODO
    return User("todo", "todo");
}

//------------------------------------------------- Surcharge d'opérateurs
AirWatcher &AirWatcher::operator=(const AirWatcher &unAirWatcher)
// Algorithme :
//
{
    return *this;
} //----- Fin de operator =

void printError(string message, int errorCode)
{
    cout << message;
    switch (errorCode)
    {
    case DataLoader::LoadError::NO_ERROR:
        cout << "No error" << endl;
        break;
    case DataLoader::LoadError::FILE_ERROR:
        cout << "File error" << endl;
        break;
    case DataLoader::LoadError::PARSE_ERROR:
        cout << "Parse error" << endl;
        break;
    case DataLoader::LoadError::CONVERT_ERROR:
        cout << "Convert error" << endl;
        break;
    default:
        cout << "Unknown error" << endl;
        break;
    }
}

//-------------------------------------------- Constructeurs - destructeur
AirWatcher::AirWatcher(const AirWatcher &unAirWatcher)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <AirWatcher>" << endl;
#endif
    printError("Loading sensors : ", DataLoader::loadSensors(sensorslist));
    printError("Loading users : ", DataLoader::loadUsers(userslist));
    printError("Loading providers : ", DataLoader::loadProviders(providerslist, cleanerslist));
    printError("Loading measurements : ", DataLoader::loadMeasurements(measurements, attributes));

    cout << "Sensors loaded: " << sensorslist.size() << endl;
    cout << "Users loaded: " << userslist.size() << endl;
    cout << "Providers loaded: " << providerslist.size() << endl;
    cout << "Cleaners loaded: " << cleanerslist.size() << endl;
    cout << "Attributes loaded: " << attributes.size() << endl;
    long long totalMeasurements = 0;
    for (auto &pair : measurements)
    {
        totalMeasurements += pair.second.size();
    }
    cout << "Measurements loaded: " << totalMeasurements << endl;
} //----- Fin de AirWatcher (constructeur de copie)

AirWatcher::AirWatcher()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <AirWatcher>" << endl;
#endif

    printError("Loading sensors : ", DataLoader::loadSensors(sensorslist));
    printError("Loading users : ", DataLoader::loadUsers(userslist));
    printError("Loading providers : ", DataLoader::loadProviders(providerslist, cleanerslist));
    printError("Loading measurements : ", DataLoader::loadMeasurements(measurements, attributes));

    cout << "Sensors loaded: " << sensorslist.size() << endl;
    cout << "Users loaded: " << userslist.size() << endl;
    cout << "Providers loaded: " << providerslist.size() << endl;
    cout << "Cleaners loaded: " << cleanerslist.size() << endl;
    cout << "Attributes loaded: " << attributes.size() << endl;
    long long totalMeasurements = 0;
    for (auto &pair : measurements)
    {
        totalMeasurements += pair.second.size();
    }
    cout << "Measurements loaded: " << totalMeasurements << endl;
} //----- Fin de AirWatcher

AirWatcher::~AirWatcher()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <AirWatcher>" << endl;
#endif
} //----- Fin de ~AirWatcher

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
