
/*************************************************************************
                           PrivateUser  -  description
                             -------------------
    début                : 16/05/2025
    copyright            : (C) 2025 par Ewan
    e-mail               : ---
*************************************************************************/

//---------- Réalisation de la classe <PrivateUser> (fichier PrivateUser.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include <string>
#include "PrivateUser.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type PrivateUser::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur

bool PrivateUser::isReliable() const
{
    return reliable;
}


void PrivateUser::setReliable(bool value)
{
    reliable = value;
}


void PrivateUser::givePoints(int pts)
{
    points += pts;
}

int PrivateUser::getPoints()
{
    return points;
}

PrivateUser::PrivateUser (int id, string passwd)
// Algorithme :
: User(id, passwd), reliable(true), points(0)
{
#ifdef MAP
cout << "Appel au constructeur de <PrivateUser>" << endl;
#endif
}


PrivateUser::~PrivateUser ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <PrivateUser>" << endl;
#endif
} //----- Fin de ~PrivateUser


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
