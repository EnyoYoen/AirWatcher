/*************************************************************************
                           AirWatcher  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <AirWatcher> (fichier AirWatcher.h) ----------------
#if !defined(AirWatcher_H)
#define AirWatcher_H

//--------------------------------------------------- Interfaces utilisées

#include <iostream>
#include <string>
#include <list>
#include <cstdbool>
#include <ctime>
#include <unordered_map>
#include <optional>

#include "../model/Sensor.h"
#include "../model/PrivateUser.h"
#include "../model/Cleaner.h"
#include "../model/Provider.h"
#include "../model/User.h"
#include "../model/Attribute.h"
#include "../ui/Menu.h"

using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <AirWatcher>
//
//
//------------------------------------------------------------------------

class AirWatcher
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------- Surcharge d'opérateurs
    AirWatcher &operator=(const AirWatcher &unAirWatcher);
    // Mode d'emploi :
    //
    // Contrat :
    //

    //-------------------------------------------- Constructeurs - destructeur
    AirWatcher(const AirWatcher &unAirWatcher);
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    AirWatcher();
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~AirWatcher();
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE
protected:
    //----------------------------------------------------- Méthodes protégées
    list<Sensor> findSimilarSensors(string sensorId);
    // Mode d'emploi :
    //
    // Contrat :
    //

    float calculateAirQuality(time_t startTime, time_t endTime, double radius, double latitude, double longitude);
    // Mode d'emploi :
    //
    // Contrat :
    //

    float measureCleanerImpact(string cleanerId);
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool checkMalfunction(string sensorId);
    // Mode d'emploi :
    //
    // Contrat :
    //

    float pointAirQuality(double latitude, double longitude, time_t time);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void awardPoints(string sensorId);
    // Mode d'emploi :
    //
    // Contrat :
    //

    optional<User> login(string userId, string password);
    // Mode d'emploi :
    //
    // Contrat :
    //

    list<Sensor> checkMalfunctionSensors();

    bool banUser(string userId);

    //----------------------------------------------------- Attributs protégés

    void startMenu();
    void printError(const string &message, int errorCode);
    void loadData();
    bool isSimilar(const Sensor &sensor1, const Sensor &sensor2, const vector<Measurement> &measurements1, const vector<Measurement> &measurements2);
    unordered_map<string, pair<float, float>> varMean(const vector<Measurement> &measurements);

    Menu menu;

    unordered_map<string, Attribute> attributes;
    unordered_map<string, vector<Measurement>> measurements;
    unordered_map<string, Sensor> sensors;
    unordered_map<string, Cleaner> cleaners;
    unordered_map<string, Provider> providers;
    unordered_map<string, PrivateUser> privateUsers;
    unordered_map<string, User> users;
    unordered_map<string, string> sensorIdToUserId; // Maps sensor IDs to user IDs for easy access
};

//-------------------------------- Autres définitions dépendantes de <AirWatcher>

#endif // AirWatcher_H
