/*************************************************************************
                           Admin  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Admin> (fichier Admin.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Admin.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Admin::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

//------------------------------------------------- Surcharge d'opérateurs
Admin &Admin::operator=(const Admin &unAdmin)
// Algorithme :
//
{
    User::operator=(unAdmin);
    this->password = unAdmin.password;
    return *this;
} //----- Fin de operator =

//-------------------------------------------- Constructeurs - destructeur
Admin::Admin(const Admin &unAdmin) : User(unAdmin), password(unAdmin.password)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Admin>" << endl;
#endif
} //----- Fin de Admin (constructeur de copie)

Admin::Admin() : User("admin"), password("admin123")
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Admin>" << endl;
#endif
} //----- Fin de Admin

Admin::~Admin()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Admin>" << endl;
#endif
} //----- Fin de ~Admin

bool Admin::connecter(string passwd) const
{
    return (passwd == password);
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
