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
#include <array>

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

unordered_map<string, pair<float, float>> AirWatcher::varMean(const vector<Measurement> &measurements)
{
    unordered_map<string, pair<float, float>> result;

    if (measurements.empty())
        return result;

    unordered_map<string, vector<float>> attributeValues;

    for (const Measurement &measurement : measurements)
    {
        attributeValues[measurement.getAttribute()].push_back(measurement.getValue());
    }

    for (const auto &pair : attributeValues)
    {
        const string &attribute = pair.first;
        const vector<float> &values = pair.second;

        for (float value : values)
        {
            result[attribute].first += value;          // Sum
            result[attribute].second += value * value; // Sum of squares
        }

        size_t n = values.size();

        if (n > 0)
        {
            result[attribute].first /= n;                                                                                    // Mean
            result[attribute].second = (result[attribute].second / n) - (result[attribute].first * result[attribute].first); // Variance
        }
        else
        {
            result[attribute] = {0.0, 0.0}; // If no values, set mean and variance to 0
        }
    }

    return result;
}

int AirWatcher::isSimilar(const Sensor &sensor1, const Sensor &sensor2, const vector<Measurement> &measurements1, const vector<Measurement> &measurements2)
{
    if (sensor1.getSensorId() == sensor2.getSensorId())
    {
        return -1; // Same sensor, not considered similar
    }

    auto varMean1 = varMean(measurements1);
    auto varMean2 = varMean(measurements2);

    float var1 = 0.0, var2 = 0.0;
    float mean1 = 0.0, mean2 = 0.0;
    string attrId;
    for (const auto &attribute : varMean1)
    {
        attrId = attribute.first;
        if (varMean2.find(attrId) != varMean2.end())
        {
            var1 += attribute.second.second; // Variance
            mean1 += attribute.second.first; // Mean
            var2 += varMean2[attrId].second; // Variance
            mean2 += varMean2[attrId].first; // Mean
        }
    }

    const double meanThreshold = 5.0; // adjust as needed
    const double varThreshold = 0.5;  // adjust as needed

    double varDiff = abs(var1 - var2);
    double meanDiff = abs(mean1 - mean2);

    if (varDiff > varThreshold || meanDiff > meanThreshold)
    {
        return -1; // Sensors are not similar
    }

    return varDiff + meanDiff;
}

list<Sensor> AirWatcher::findSimilarSensors(string sensorId)
{
    clock_t startClock = clock();
    Sensor sensor = sensors[sensorId];
    list<Sensor> similarSensors;
    list<int> similarityScores;
    for (const auto &pair : sensors)
    {
        const Sensor &otherSensor = pair.second;
        int similarityScore = isSimilar(sensor, otherSensor, measurements[sensorId], measurements[otherSensor.getSensorId()]);
        if (otherSensor.getSensorId() != sensorId && otherSensor.isReliable() && similarityScore > 0)
        {
            similarityScores.push_back(similarityScore);
            similarSensors.push_back(otherSensor);
        }
    }
    menu.debug("Finding similar sensors took " + to_string(double(clock() - startClock) / CLOCKS_PER_SEC) + " seconds.\n");

    // Sort similarSensors based on similarity scores (descending order)
    vector<pair<int, Sensor>> scoredSensors;
    auto simIt = similarityScores.begin();
    auto sensIt = similarSensors.begin();
    while (simIt != similarityScores.end() && sensIt != similarSensors.end())
    {
        scoredSensors.emplace_back(*simIt, *sensIt);
        ++simIt;
        ++sensIt;
    }
    sort(scoredSensors.begin(), scoredSensors.end(), [](const pair<int, Sensor> &a, const pair<int, Sensor> &b)
         { return a.first < b.first; });
    similarSensors.clear();
    for (const auto &p : scoredSensors)
    {
        similarSensors.push_back(p.second);
    }

    return similarSensors;
}

// This function calculates the average air quality index (AQI) for sensors within a given radius and time range.
// If no valid air quality data is found, the function returns -1.
float AirWatcher::calculateAirQuality(time_t startTime, time_t endTime, double radius, double latitude, double longitude)
{
    clock_t startClock = clock();

    float averageAQI = 0;
    int count = 0;
    for (const auto &pair : sensors)
    {
        const Sensor &sensor = pair.second;
        if (sensor.checkDistance(latitude, longitude, radius) && sensor.isReliable())
        {
            float airQuality = sensor.calculateAirQuality(startTime, endTime, measurements[sensor.getSensorId()]);
            if (airQuality > 0)
            {
                awardPoints(sensor.getSensorId()); // Award points for the sensor
                averageAQI += airQuality;
                count++;
            }
        }
    }

    clock_t endClock = clock();
    double elapsedTime = double(endClock - startClock) / CLOCKS_PER_SEC;
    menu.debug("Air quality calculation took " + to_string(elapsedTime) + " seconds.\n");

    return (count > 0) ? (averageAQI / count) : -1;
}

bool AirWatcher::measureCleanerImpact(string cleanerId, float *res)
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
        return false; // Cleaner not found
    }
    // Get the key (cleanerId)
    Cleaner cleaner = it->second;
    startTime = cleaner.getStartTime();
    stopTime = cleaner.getStopTime();
    latitude = cleaner.getLatitude();
    longitude = cleaner.getLongitude();

    int count = 0;

    // Analyse des mesures pour calculer l'impact
    for (const auto &pair : sensors)
    {
        const Sensor &sensor = pair.second;
        const string &sensorId = pair.first;
        if (sensor.checkDistance(latitude, longitude, 100) && sensor.isReliable())
        {
            awardPoints(sensorId); // Award points for the sensor
            ++count;
            float beforeAQI = sensor.calculateAirQuality(startTime - 86400, startTime, measurements[sensorId]); // 1 day before
            float afterAQI = sensor.calculateAirQuality(stopTime, stopTime + 86400, measurements[sensorId]);    // 1 day after
            if (beforeAQI > 0 && afterAQI > 0)
            {
                improvement += ((beforeAQI - afterAQI) / beforeAQI) * 100; // Percentage improvement
            }
        }
    }

    clock_t endClock = clock();
    double elapsedTime = double(endClock - startClock) / CLOCKS_PER_SEC;
    menu.debug("Cleaner impact calculation took " + to_string(elapsedTime) + " seconds.\n");

    if (count > 0)
    {
        *res = improvement / count; // Average improvement
    }

    return (count > 0);
}

bool AirWatcher::checkMalfunction(string sensorId)
{
    clock_t startClock = clock();
    const float threshold = 5.0;

    auto mit = measurements.find(sensorId);
    if (mit == measurements.end())
    {
        menu.error("No measurements found for sensor: " + sensorId);
        return false;
    }
    vector<Measurement> &sensorMeasurements = mit->second;

    auto varMeanResult = varMean(sensorMeasurements);

    for (const auto &entry : varMeanResult)
    {
        const string &attributeId = entry.first;
        const pair<float, float> &varMeanPair = entry.second;

        if (varMeanPair.second > threshold || varMeanPair.first < 0.0)
        {
            sensors[sensorId].banSensor(); // Ban the sensor if it is malfunctioning
            menu.debug("Finding malfunction for sensor " + sensorId + " took " + to_string(double(clock() - startClock) / CLOCKS_PER_SEC) + " seconds.\n");
            return true; // Sensor is malfunctioning
        }
    }
    menu.debug("Finding malfunction for sensor " + sensorId + " took " + to_string(double(clock() - startClock) / CLOCKS_PER_SEC) + " seconds.\n");

    return false;
}

float AirWatcher::pointAirQuality(double latitude, double longitude, time_t time)
{
    // TODO
    return 0.0;
}

void AirWatcher::awardPoints(string sensorId)
{
    auto it = sensorIdToUserId.find(sensorId);
    if (it == sensorIdToUserId.end())
    {
        return; // Sensor ID not found
    }
    User &user = users[it->second];
    ((PrivateUser &)user).addPoints();
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
            sensorIdToUserId[sensorId] = userId;
        }
    }

    menu.debug("Sensors loaded: " + to_string(sensors.size()));
    menu.debug("Private users loaded: " + to_string(privateUsers.size()));
    menu.debug("Users loaded: " + to_string(users.size()));
    menu.debug("Providers loaded: " + to_string(providers.size()));
    menu.debug("Cleaners loaded: " + to_string(cleaners.size()));
    menu.debug("Attributes loaded: " + to_string(attributes.size()));
    menu.debug("Sensor to user ID mapping loaded: " + to_string(sensorIdToUserId.size()));

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
    string sensorId;
    string userId;
    string cleanerId;
    float valueAQI;
    tuple<time_t, time_t, double, double, double> airQualite;

    MenuRights rights = MenuRights::NOT_LOGGED_IN;
    MenuChoice choice = menu.mainMenu(rights);

    while (choice != MenuChoice::EXIT)
    {
        float res = 0.0;
        tuple<time_t, time_t, double, double, double> t;
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
            airQualite = menu.airQualityMenu();
            valueAQI = calculateAirQuality(get<0>(airQualite), get<1>(airQualite), get<4>(airQualite), get<2>(airQualite), get<3>(airQualite));
            if (valueAQI == -1)
                menu.error("No valid air quality data found for the specified parameters.");
            else
                menu.printQualiteAir(valueAQI);
            break;
        case MenuChoice::POINT_AIR_QUALITY_MENU:
            menu.pointAirQualityMenu();
            break;
        case MenuChoice::CLEANER_IMPACT_MENU:
            cleanerId = menu.cleanerImpactMenu(cleaners);
            menu.printCleanerImpact(cleaners[cleanerId], measureCleanerImpact(cleanerId, &res), &res);
            break;
        case MenuChoice::FIND_SIMILAR_SENSORS_MENU:
            sensorId = menu.findSimilarSensorsMenu(sensors);
            menu.printSimilarSensors(findSimilarSensors(sensorId));
            break;
        case MenuChoice::CHECK_ONE_MALFUNCTION_MENU:
            sensorId = menu.checkOneMalfunctionMenu(sensors);
            menu.printOneMalfunctionSensor(sensors[sensorId], checkMalfunction(sensorId));
            break;
        case MenuChoice::CHECK_MALFUNCTION_MENU:
            menu.printMalfunctionSensors(checkMalfunctionSensors());
            break;
        case MenuChoice::BAN_USER_MENU:
            userId = menu.banUserMenu(privateUsers);
            menu.printBannedUser(users[userId], banUser(userId));
            break;
        default:
            menu.error("Invalid choice");
            break;
        }
        choice = menu.mainMenu(rights);
    }
}

list<Sensor> AirWatcher::checkMalfunctionSensors()
{
    list<Sensor> malfunctioningSensors;
    for (const auto &pair : sensors)
    {
        const Sensor &sensor = pair.second;
        if (checkMalfunction(sensor.getSensorId()))
        {
            malfunctioningSensors.push_back(sensor);
        }
    }
    return malfunctioningSensors;
}

bool AirWatcher::banUser(string userId)
{
    auto it = privateUsers.find(userId);
    if (it == privateUsers.end())
    {
        return false;
    }

    PrivateUser &privateUser = it->second;
    privateUser.setReliable(false);
    for (const string &sensorId : privateUser.getSensorIds())
    {
        sensors[sensorId].banSensor();
    }
    menu.debug("User " + userId + " has been banned.");
    return true;
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
