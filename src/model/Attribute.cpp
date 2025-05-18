/*************************************************************************
                           Attribute  -  description
                             -------------------
    début                : 16/02/2025
    copyright            : (C) 2025 par Ewan
    e-mail               : ---
*************************************************************************/

//---------- Réalisation de la classe <Attribute> (fichier Attribute.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <string>

//------------------------------------------------------ Include personnel
#include "Attribute.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

Attribute::Attribute(string unAttributeId, string unUnit, string uneDescription)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Attribute>" << endl;
#endif

    attributeId = unAttributeId;
    unit = unUnit;
    description = uneDescription;
} //----- Fin de Attribute

Attribute::~Attribute()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Attribute>" << endl;
#endif
} //----- Fin de ~Attribute

string Attribute::getAttributeId()
{
    return attributeId;
}

string Attribute::getUnit()
{
    return unit;
}

string Attribute::getDescription()
{
    return description;
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
