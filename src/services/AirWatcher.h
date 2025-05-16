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
#include "Sensor.h"
#include "PrivateUser.h"
#include "Cleaner.h"
#include "Provider.h"
#include "User.h"

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

    float calculateAirQuality(time_t startTime, time_t endTime, float radius, float latitude, float longitude);
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool checkMalfunction(long sensorId);
    // Mode d'emploi :
    //
    // Contrat :
    //

    float pointAirQuality(float latitude, float longitude, time_t time);
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

    bool loadDataFromFile(string fileName);
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

    //----------------------------------------------------- Attributs protégés

    list<Sensor> sensorList;
    list<PrivateUser> privateUsersList;
    list<Cleaner> cleanersList;
    list<Provider> providersList;
    list<User> usersList;
};

//-------------------------------- Autres définitions dépendantes de <AirWatcher>

#endif // AirWatcher_H
