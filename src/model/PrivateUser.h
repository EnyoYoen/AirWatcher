/*************************************************************************
                           PrivateUser  -  description
                             -------------------
    début                : 16/05/2025
    copyright            : (C) 2025 par Ewan
    e-mail               : ---
*************************************************************************/

//---------- Interface de la classe <PrivateUser> (fichier PrivateUser.h) ----------------
#if !defined(PRIVATE_USER_H)
#define PRIVATE_USER_H

#include <string>
#include <list>

//--------------------------------------------------- Interfaces utilisées
#include "User.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <PrivateUser>
//
//
//------------------------------------------------------------------------

class PrivateUser : public User
{
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //

    //-------------------------------------------- Constructeurs - destructeur
    PrivateUser();

    PrivateUser(string id);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~PrivateUser();
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool isReliable() const;
    // Mode d'emploi :
    // Accéder à 'reliable'
    // Contrat :
    //

    void setReliable(bool value);
    // Mode d'emploi :
    // Accéder à 'reliable'
    // Contrat :
    //

    int getPoints();
    // Mode d'emploi :
    // Accéder à 'points'
    // Contrat :
    //
    void givePoints(int pts);
    // Mode d'emploi :
    // Ajouter ou enlever des points
    // Contrat :
    //

    list<string> getSensorIds() const;

    void addSensor(string sensorId);
    bool connecter(string passwd) const override;

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
    bool reliable;
    int points;
    list<string> sensorIds;
};

//-------------------------------- Autres définitions dépendantes de <Xxx>

#endif // PRIVATE_USER_H
