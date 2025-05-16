/*************************************************************************
                           Cleaner  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Cleaner> (fichier Cleaner.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Cleaner.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Cleaner::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

std::string Cleaner::getCleanerId()
{
    return this->cleanerId;
}

//------------------------------------------------- Surcharge d'opérateurs
Cleaner & Cleaner::operator = ( const Cleaner & unCleaner )
// Algorithme :
//
{
    if (this != &unCleaner) {
        this->cleanerId = unCleaner.cleanerId;
        this->latitude = unCleaner.latitude; 
        this->longitude = unCleaner.longitude;
        this->startTime = unCleaner.startTime;
        this->stopTime = unCleaner.stopTime;
    }

    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Cleaner::Cleaner ( const Cleaner & unCleaner ) :
    cleanerId(unCleaner.cleanerId), latitude(unCleaner.latitude), longitude(unCleaner.longitude), startTime(unCleaner.startTime), stopTime(unCleaner.stopTime)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Cleaner>" << endl;
#endif
} //----- Fin de Cleaner (constructeur de copie)


Cleaner::Cleaner ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Cleaner>" << endl;
#endif
} //----- Fin de Cleaner

Cleaner::Cleaner (std::string unCleanerId, double uneLatitude, double uneLongitude,  time_t unStartTime, time_t unStopTime) :
    cleanerId(unCleanerId), latitude(uneLatitude), longitude(uneLongitude), startTime(unStartTime), stopTime(unStopTime)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Cleaner>" << endl;
#endif
} //----- Fin de Cleaner


Cleaner::~Cleaner ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Cleaner>" << endl;
#endif
} //----- Fin de ~Cleaner


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

