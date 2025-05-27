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

list<Sensor> AirWatcher::findSimilarSensors(string sensorId)
{
    list<Sensor> placeholder;
    return placeholder;
}

float AirWatcher::calculateAirQuality(time_t startTime, time_t endTime, double radius, double latitude, double longitude)
{
    clock_t startClock = clock();

    float averageAQI = 0;
    int count = 0;

    for (auto &it : sensorslist)
    {
        Sensor sensor = it.second;
        if (sensor.checkDistance(latitude, longitude, radius))
        {
            float airQuality = sensor.calculateAirQuality(startTime, endTime, measurements[sensor.getSensorId()]);
            if (airQuality > 0)
            {
                averageAQI += airQuality;
                count++;
            }
        }
    }

    clock_t endClock = clock();
    double elapsedTime = double(endClock - startClock) / CLOCKS_PER_SEC;
    printf("Cleaner impact calculation took %.2f seconds.\n", elapsedTime);

    return (count > 0) ? (averageAQI / count) : -1;
}

float AirWatcher::measureCleanerImpact(string cleanerId) const
{
    clock_t startClock = clock();
    time_t startTime;
    time_t stopTime;
    double latitude;
    double longitude;
    float improvement = 0.0;

    // Recherche du Cleaner correspondant
    Cleaner cleaner = cleanerslist.at(cleanerId);
    if (cleaner.getCleanerId().empty())
    {
        return -1; // Cleaner not found
    }
    else
    {
        startTime = cleaner.getStartTime();
        stopTime = cleaner.getStopTime();
        latitude = cleaner.getLatitude();
        longitude = cleaner.getLongitude();
    }

    int count = 0;

    // Analyse des mesures pour calculer l'impact
    for (auto &it : sensorslist)
    {
        Sensor sensor = it.second;
        if (sensor.checkDistance(latitude, longitude, 10))
        {
            ++count;
            float beforeAQI = sensor.calculateAirQuality(startTime - 3600, startTime, measurements.at(sensor.getSensorId())); // 1 hour before
            float afterAQI = sensor.calculateAirQuality(stopTime, stopTime + 3600, measurements.at(sensor.getSensorId()));    // 1 hour after
            if (beforeAQI > 0 && afterAQI > 0)
            {
                improvement += (beforeAQI - afterAQI) / beforeAQI * 100; // Percentage improvement
            }
        }
    }

    clock_t endClock = clock();
    double elapsedTime = double(endClock - startClock) / CLOCKS_PER_SEC;
    printf("Cleaner impact calculation took %.2f seconds.\n", elapsedTime);

    return (count > 0) ? (improvement / count) : -1; // Average improvement
}

bool AirWatcher::checkMalfunction(string sensorId)
{
    Sensor sensor = sensorslist.at(sensorId);

    // TODO
    return false;
}

float AirWatcher::pointAirQuality(double latitude, double longitude, time_t time)
{
    // TODO
    return 0.0;
}

bool AirWatcher::checkUnreliableSensor(string sensorId, string userId)
{
    // TODO
    return false;
}

void AirWatcher::awardPoints(string userId)
{
    // TODO
}

User AirWatcher::login(string userId, string password)
{
    User user = userslist.at(userId);
    if (user.getUserId().empty())
    {
        return User(""); // Return an invalid user if not found
    }
    if (user.connecter(password))
    {
        return user; // Return the user if login is successful
    }

    menu.error("Login failed: Invalid user ID or password.");
    return User(""); // Return an invalid user if login fails
}

//------------------------------------------------- Surcharge d'opérateurs
AirWatcher &AirWatcher::operator=(const AirWatcher &unAirWatcher)
// Algorithme :
//
{
    return *this;
} //----- Fin de operator =

void AirWatcher::printError(const string &message, int errorCode)
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
    printError("Loading users : ", DataLoader::loadUsers(userslist, privateUserslist));
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
    // ofstream *logStream = new ofstream("log.txt");
    // menu.setLogStream(logStream);
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
