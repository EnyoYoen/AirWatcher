/*************************************************************************
                           Measurement - represents a sensor measurement
                             -------------------
    début                : 16/05/2025
    copyright            : (C) 2025 par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Xxx> (fichier Xxx.h) ----------------
#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <iostream>
#include <string>
#include <list>
#include <ctime>

using namespace std;

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

class Measurement
{
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques
    string getAttribute() const;
    float getValue() const;
    time_t getTimestamp() const;

    //-------------------------------------------- Constructeurs - destructeur
    Measurement(const time_t &timestamp, const string &attributeid, float value);
    Measurement(const Measurement &other);
    ~Measurement();

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
    time_t timestamp;
    string attributeId;
    float value;
};

//-------------------------------- Autres définitions dépendantes de <Xxx>

#endif // MEASUREMENT_H
