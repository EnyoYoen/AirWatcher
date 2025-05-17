/*************************************************************************
                           User  -  description
                             -------------------
    début                :  2025
    copyright            : (C) 2025 par Ewan
    e-mail               : ---
*************************************************************************/

//---------- Interface de la classe <User> (fichier User.h) ----------------
#if ! defined ( USER_H )
#define USER_H

//--------------------------------------------------- Interfaces utilisées

#include <string>

using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <User>
//
//
//------------------------------------------------------------------------

class User
{
//----------------------------------------------------------------- PUBLIC


public:
      User(string id, string mdp);
      // Mode d'emploi (constructeur de copie) :
      //
      // Contrat :
      //

      User(const User& unUser);
      // Mode d'emploi (constructeur de copie) :
      //
      // Contrat :
      //

      string getUserId() const;

      bool Connecter(string passwd);
      // Mode d'emploi (constructeur de copie) :
      //        Verifie si le mot de passe est correcte
      // Contrat :
      //
      ~User();
      // Mode d'emploi (constructeur de copie) :
      //
      // Contrat :
      //
  private:
      
      string userId;
      string password;

};

//-------------------------------- Autres définitions dépendantes de <Xxx>

#endif // USER_H
