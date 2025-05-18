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
#include <fstream>

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

<<<<<<< HEAD
void printError(string message, int errorCode)
=======

void AirWatcher::printError(const string& message, int errorCode)
>>>>>>> d64073bfa31e812b918220df24734d67192f1a96
{
    string finalMessage = message;
    switch (errorCode)
    {
    case DataLoader::LoadError::NO_ERROR:
        finalMessage += "No error";
        break;
    case DataLoader::LoadError::FILE_ERROR:
        finalMessage += "File error";
        break;
    case DataLoader::LoadError::PARSE_ERROR:
        finalMessage += "Parse error";
        break;
    case DataLoader::LoadError::CONVERT_ERROR:
        finalMessage += "Convert error";
        break;
    default:
        finalMessage += "Unknown error";
        break;
    }
    
    if (errorCode != DataLoader::LoadError::NO_ERROR)
    {
        menu.error(finalMessage);
    }
    else
    {
        menu.debug(finalMessage);
    }
}

void AirWatcher::loadData()
{
    printError("Loading sensors : ", DataLoader::loadSensors(sensorslist));
    printError("Loading users : ", DataLoader::loadUsers(userslist));
    printError("Loading providers : ", DataLoader::loadProviders(providerslist, cleanerslist));
    printError("Loading measurements : ", DataLoader::loadMeasurements(measurements, attributes));

    menu.debug("Sensors loaded: " + to_string(sensorslist.size()));
    menu.debug("Users loaded: " + to_string(userslist.size()));
    menu.debug("Providers loaded: " + to_string(providerslist.size()));
    menu.debug("Cleaners loaded: " + to_string(cleanerslist.size()));
    menu.debug("Attributes loaded: " + to_string(attributes.size()));

    long long totalMeasurements = 0;
    for (auto &pair : measurements)
    {
        totalMeasurements += pair.second.size();
    }
    menu.debug("Measurements loaded: " + to_string(totalMeasurements));
}

void AirWatcher::startMenu()
{
    MenuChoice choice = menu.mainMenu();
    while (choice != MenuChoice::EXIT)
    {
        switch (choice)
        {
        case MenuChoice::LOGIN_MENU:
            menu.loginMenu();
            break;
        case MenuChoice::AIR_QUALITY_MENU:
            menu.airQualityMenu();
            break;
        case MenuChoice::POINT_AIR_QUALITY_MENU:
            menu.pointAirQualityMenu();
            break;
        case MenuChoice::CLEANER_IMPACT_MENU:
            menu.cleanerImpactMenu(cleanerslist);
            break;
        case MenuChoice::FIND_SIMILAR_SENSORS_MENU:
            menu.findSimilarSensorsMenu(sensorslist);
            break;
        case MenuChoice::CHECK_MALFUNCTION_MENU:
            menu.checkMalfunctionMenu(sensorslist);
            break;
        case MenuChoice::CHECK_UNRELIABLE_MENU:
            menu.checkUnreliableMenu(sensorslist, userslist);
            break;
        case MenuChoice::AWARD_POINTS_MENU:
            menu.awardPointsMenu(userslist);
            break;
        default:
            menu.error("Invalid choice");
            break;
        }
        choice = menu.mainMenu();
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
    this->menu = unAirWatcher.menu;
    this->sensorslist = unAirWatcher.sensorslist;
    this->providerslist = unAirWatcher.providerslist;
    this->cleanerslist = unAirWatcher.cleanerslist;
    this->measurements = unAirWatcher.measurements;
    this->attributes = unAirWatcher.attributes;
    this->privateUserslist = unAirWatcher.privateUserslist;
    this->userslist = unAirWatcher.userslist;

    startMenu();
} //----- Fin de AirWatcher (constructeur de copie)

AirWatcher::AirWatcher()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <AirWatcher>" << endl;
#endif
    //ofstream *logStream = new ofstream("log.txt");
    //menu.setLogStream(logStream);
    menu.setLogStream(&cout);
    
    loadData();

    startMenu();
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
