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
#include <algorithm>
#include <numeric>

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
    for (auto &pair : sensors)
    {
        Sensor sensor = pair.second;
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
    menu.debug("Cleaner impact calculation took " + to_string(elapsedTime) + " seconds.\n");

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
    auto it = cleaners.find(cleanerId);
    if (it == cleaners.end())
    {
        return -1; // Cleaner not found
    }
    // Get the key (cleanerId)
    else
    {
        Cleaner cleaner = it->second;
        startTime = cleaner.getStartTime();
        stopTime = cleaner.getStopTime();
        latitude = cleaner.getLatitude();
        longitude = cleaner.getLongitude();
    }

    int count = 0;

    // Analyse des mesures pour calculer l'impact
    for (const auto &pair : sensors)
    {
        const Sensor &sensor = pair.second;
        const string &sensorId = pair.first;
        if (sensor.checkDistance(latitude, longitude, 10))
        {
            ++count;
            float beforeAQI = sensor.calculateAirQuality(startTime - 3600, startTime, measurements.at(sensorId)); // 1 hour before
            float afterAQI = sensor.calculateAirQuality(stopTime, stopTime + 3600, measurements.at(sensorId));    // 1 hour after
            if (beforeAQI > 0 && afterAQI > 0)
            {
                improvement += (beforeAQI - afterAQI) / beforeAQI * 100; // Percentage improvement
            }
        }
    }

    clock_t endClock = clock();
    double elapsedTime = double(endClock - startClock) / CLOCKS_PER_SEC;
    menu.debug("Cleaner impact calculation took " + to_string(elapsedTime) + " seconds.\n");

    return (count > 0) ? (improvement / count) : -1; // Average improvement
}

bool AirWatcher::checkMalfunction(string sensorId)
{
    const float threshold = 3.0;

    auto it = sensors.find(sensorId);
    if (it == sensors.end())
    {
        menu.error("Sensor not found: " + sensorId);
        return false;
    }

    Sensor sensor = it->second;
    auto mit = measurements.find(sensorId);
    if (mit == measurements.end())
    {
        return false;
    }
    vector<Measurement> &sensorMeasurements = mit->second;
    sort(sensorMeasurements.begin(), sensorMeasurements.end(),
         [](const Measurement &a, const Measurement &b)
         {
             return a.getTimestamp() < b.getTimestamp();
         });

    unsigned long long totalMeasurements = sensorMeasurements.size();
    unsigned long long inconsistentMeasurements = 0;

    unordered_map<string, float> attributeValues;
    for (const Measurement &measurement : sensorMeasurements)
    {
        const string &attributeId = measurement.getAttribute();
        float value = measurement.getValue();
        if (attributeValues.find(attributeId) == attributeValues.end())
        {
            attributeValues[attributeId] = value;
        }
        else
        {
            if (abs(value - attributeValues[attributeId]) > threshold)
            {
                inconsistentMeasurements++;
            }
            attributeValues[attributeId] = value;
        }
    }

    /*unordered_map<string, vector<float>> attributeAllValues;
    for (const Measurement &measurement : sensorMeasurements)
    {
        attributeAllValues[measurement.getAttribute()].push_back(measurement.getValue());
    }

    for (const auto &pair : attributeAllValues)
    {
        const vector<float> &values = pair.second;
        if (values.size() > 1)
        {
            float mean = accumulate(values.begin(), values.end(), 0.0f) / values.size();
            float variance = 0.0f;
            for (float v : values)
            {
                variance += (v - mean) * (v - mean);
            }
            variance /= (values.size() - 1);
            menu.debug("Variance for " + pair.first + " on sensor " + sensorId + " : " + to_string(variance));
        }
    }*/

    return (inconsistentMeasurements > totalMeasurements * 0.05);
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
    User user = users.at(userId);
    if (user.getUserId().empty())
    {
        return;
    }
    user.addPoints();
}

optional<User> AirWatcher::login(string userId, string password)
{
    auto it = users.find(userId);
    if (it == users.end())
    {

        menu.error("Login failed: User ID not found.");
        return optional<User>(); // Return an empty optional if user ID is not found
    }
    User user = it->second;
    if (user.connecter(password))
    {
        return user; // Return the user if login is successful
    }

    menu.error("Login failed: Invalid user ID or password.");
    return optional<User>(); // Return an empty optional if login fails
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
    printError("Loading sensors : ", DataLoader::loadSensors(sensors));
    printError("Loading users : ", DataLoader::loadUsers(users, privateUsers));
    printError("Loading providers : ", DataLoader::loadProviders(providers, cleaners));
    printError("Loading measurements : ", DataLoader::loadMeasurements(measurements, attributes));

    for (const auto &pair : privateUsers)
    {
        const PrivateUser &privateUser = pair.second;
        const string &userId = pair.first;
        for (const string &sensorId : privateUser.getSensorIds())
        {
            sensorToUserId[sensorId] = userId;
        }
    }

    menu.debug("Sensors loaded: " + to_string(sensors.size()));
    menu.debug("Private users loaded: " + to_string(privateUsers.size()));
    menu.debug("Users loaded: " + to_string(users.size()));
    menu.debug("Providers loaded: " + to_string(providers.size()));
    menu.debug("Cleaners loaded: " + to_string(cleaners.size()));
    menu.debug("Attributes loaded: " + to_string(attributes.size()));
    menu.debug("Sensor to user ID mapping loaded: " + to_string(sensorToUserId.size()));

    long long totalMeasurements = 0;
    for (auto &pair : measurements)
    {
        totalMeasurements += pair.second.size();
    }
    menu.debug("Measurements loaded: " + to_string(totalMeasurements));
}

void AirWatcher::startMenu()
{
    pair<string, string> credentials;
    optional<User> user;

    MenuRights rights = MenuRights::NOT_LOGGED_IN;
    MenuChoice choice = menu.mainMenu(rights);

    while (choice != MenuChoice::EXIT)
    {
        switch (choice)
        {
        case MenuChoice::LOGIN_MENU:
            credentials = menu.loginMenu();
            user = login(credentials.first, credentials.second);
            if (user.has_value())
            {
                menu.debug("Login successful for user: " + user->getUserId());
                if (dynamic_cast<PrivateUser *>(&*user))
                {
                    rights = MenuRights::PRIVATE_USER;
                }
                else
                {
                    rights = MenuRights::ADMIN;
                }
            }
            break;
        case MenuChoice::AIR_QUALITY_MENU:
            menu.airQualityMenu();
            break;
        case MenuChoice::POINT_AIR_QUALITY_MENU:
            menu.pointAirQualityMenu();
            break;
        case MenuChoice::CLEANER_IMPACT_MENU:
            menu.cleanerImpactMenu(cleaners);
            break;
        case MenuChoice::FIND_SIMILAR_SENSORS_MENU:
            menu.findSimilarSensorsMenu(sensors);
            break;
        case MenuChoice::CHECK_MALFUNCTION_MENU:
            if (checkMalfunction(menu.checkMalfunctionMenu(sensors)))
            {
                menu.debug("Sensor is malfunctioning.");
            }
            break;
        case MenuChoice::CHECK_UNRELIABLE_MENU:
            menu.checkUnreliableMenu(sensors, users);
            break;
        default:
            menu.error("Invalid choice");
            break;
        }
        choice = menu.mainMenu(rights);
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
    this->sensors = unAirWatcher.sensors;
    this->providers = unAirWatcher.providers;
    this->cleaners = unAirWatcher.cleaners;
    this->measurements = unAirWatcher.measurements;
    this->attributes = unAirWatcher.attributes;
    this->privateUsers = unAirWatcher.privateUsers;
    this->users = unAirWatcher.users;

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
