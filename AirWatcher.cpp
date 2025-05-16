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

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type AirWatcher::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

List<Sensor> findSimilarSensors(string sensorId);

float calculateAirQuality(time_t startTime, time_t endTime, float radius, float latitude, float longitude);

Bool checkMalfunction(string sensorId);

float pointAirQuality(float latitude, float longitude, time_t time);

float measureCleanerImpact(string cleanerId);

Bool checkUnreliableSensor(string sensorId, string userId);

void awardPoints(string userId);

Bool loadDataFromFile(string fileName);
{
}

User login(string userId, string password);

time_t parseDateTime(const char *datetimeString, const char *format)
{
    struct tm tmStruct;
    strptime(datetimeString, format, &tmStruct);
    return mktime(&tmStruct);
}

//------------------------------------------------- Surcharge d'opérateurs
AirWatcher &AirWatcher::operator=(const AirWatcher &unAirWatcher)
// Algorithme :
//
{
} //----- Fin de operator =

//-------------------------------------------- Constructeurs - destructeur
AirWatcher::AirWatcher(const AirWatcher &unAirWatcher)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <AirWatcher>" << endl;
#endif
} //----- Fin de AirWatcher (constructeur de copie)

AirWatcher::AirWatcher()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <AirWatcher>" << endl;
#endif
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
