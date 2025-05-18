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

#include "../model/Sensor.h"
#include "../model/PrivateUser.h"
#include "../model/Cleaner.h"
#include "../model/Provider.h"
#include "../model/User.h"
#include "../model/Attribute.h"
<<<<<<< HEAD
#include <stdbool.h>
#include <ctime>
#include <unordered_map>
#include <vector>
#include "DataLoader.h"
#include "Measurement.h"
#include "Attribute.h"
#include "utils/DateTime.h"
=======
#include "../ui/Menu.h"
>>>>>>> d64073bfa31e812b918220df24734d67192f1a96

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

    list<Sensor> findSimilarSensors(long sensorId);
    // Mode d'emploi :
    //
    // Contrat :
    //

    float calculateAirQuality(time_t startTime, time_t endTime, double radius, double latitude, double longitude);
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool checkMalfunction(long sensorId);
    // Mode d'emploi :
    //
    // Contrat :
    //

    float pointAirQuality(double latitude, double longitude, time_t time);
    // Mode d'emploi :
    //
    // Contrat :
    //

    float measureCleanerImpact(long cleanerId);
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool checkUnreliableSensor(long sensorId, long userId);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void awardPoints(long userId);
    // Mode d'emploi :
    //
    // Contrat :
    //

    User login(long userId, string password);
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées
    void startMenu();
    void printError(const string &message, int errorCode);
    void loadData();

    //----------------------------------------------------- Attributs protégés

    Menu menu;

    unordered_map<string, Attribute> attributes;
    unordered_map<string, vector<Measurement>> measurements;
    list<Sensor> sensorslist;
    list<Cleaner> cleanerslist;
    list<Provider> providerslist;
    list<PrivateUser> privateUserslist;
    list<User> userslist;
};

//-------------------------------- Autres définitions dépendantes de <AirWatcher>

#endif // AirWatcher_H
