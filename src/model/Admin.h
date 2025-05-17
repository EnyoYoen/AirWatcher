/*************************************************************************
                           Admin  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Admin> (fichier Admin.h) ----------------
#if ! defined ( ADMIN_H )
#define ADMIN_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Admin>
//
//
//------------------------------------------------------------------------

class Admin
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs
    Admin & operator = ( const Admin & unAdmin );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Admin ( const Admin & unAdmin );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Admin ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Admin ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <Admin>

#endif // ADMIN_H

