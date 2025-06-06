/*************************************************************************
                           Measurement  -  implements the Measurement class
                             -------------------
    début                : 16/05/2025
    copyright            : (C) 2025 par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Xxx> (fichier Xxx.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Measurement.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
string Measurement::getAttribute() const
{
  return attributeId;
}

float Measurement::getValue() const
{
  return value;
}

time_t Measurement::getTimestamp() const
{
  return timestamp;
}

//-------------------------------------------- Constructeurs - destructeur
Measurement::Measurement(const time_t &timestamp, const string &attribute, float value)
    : timestamp(timestamp), attributeId(attribute), value(value)
// Algorithme :
//
{
#ifdef MAP
  cout << "Appel au constructeur de copie de Measurement" << endl;
#endif
} //----- Fin de Measurement (constructeur de copie)

Measurement::Measurement(const Measurement &other)
    : timestamp(other.timestamp), attributeId(other.attributeId), value(other.value)
//
{
#ifdef MAP
  cout << "Appel au constructeur de Measurement" << endl;
#endif
} //----- Fin de Measurement

Measurement::~Measurement()
// Algorithme :
//
{
#ifdef MAP
  cout << "Appel au destructeur de Measurement" << endl;
#endif
} //----- Fin de ~Measurement

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
