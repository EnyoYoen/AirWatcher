/*************************************************************************
                           User  -  description
                             -------------------
    début                : 2025
    copyright            : (C) 2025 par Ewan
    e-mail               : ---
*************************************************************************/

//---------- Réalisation de la classe <User> (fichier User.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <sstream>

//------------------------------------------------------ Include personnel
#include "User.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool User::connecter(string passwd) const
{
    return (password == passwd) ? true : false;
}

string User::toString() const
{
    stringstream ss;
    ss << userId;
    return ss.str();
}

string User::getUserId() const
{
    return this->userId;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
User::User(const User &unUser)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <User>" << endl;
#endif
    userId = unUser.userId;
    password = unUser.password;
} //----- Fin de Xxx (constructeur de copie)

User::User(string id, string mdp)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <User>" << endl;
#endif
    userId = id;
    password = mdp;
} //----- Fin de User

User::~User()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <User>" << endl;
#endif
} //----- Fin de ~User

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
