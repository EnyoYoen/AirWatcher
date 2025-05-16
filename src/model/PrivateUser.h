
/*************************************************************************
                           PrivateUser  -  description
                             -------------------
    début                : 16/05/2025
    copyright            : (C) 2025 par Ewan
    e-mail               : ---
*************************************************************************/

//---------- Interface de la classe <PrivateUser> (fichier PrivateUser.h) ----------------
#if ! defined ( PRIVATE_USER_H )
#define PRIVATE_USER_H

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
    PrivateUser (int id,  std::string pwd );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~PrivateUser ( );
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

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    bool reliable;
    int points;
};

//-------------------------------- Autres définitions dépendantes de <Xxx>

#endif // PRIVATE_USER_H
