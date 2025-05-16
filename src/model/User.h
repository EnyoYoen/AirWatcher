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
      User(int id, std::string mdp);
      // Mode d'emploi (constructeur de copie) :
      //
      // Contrat :
      //

      User(const User& unUser);
      // Mode d'emploi (constructeur de copie) :
      //
      // Contrat :
      //

      ~User();
      // Mode d'emploi (constructeur de copie) :
      //
      // Contrat :
      //

  private:
      int userId;
      std::string password;

};

//-------------------------------- Autres définitions dépendantes de <Xxx>

#endif // USER_H
