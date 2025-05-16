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
Attribute Measurement::GetAttribute() const
{
    return attribute;
}

float Measurement::GetValue()const
{
  return value;
}

string Measurement::getTimestamp() const
{
  return timestamp;
}

//-------------------------------------------- Constructeurs - destructeur
Measurement::Measurement (const string& timestamp, const Attribute&attrubute, float value)
  : timestamp(timestamp), attribute(attribute), value(value)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de Measurement" << endl;
#endif
} //----- Fin de Measurement (constructeur de copie)


Measurement::Measurement(const Measurement& other)
   : timestamp(other.timestamp),attribute(other.attribute), value (other.value)
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

