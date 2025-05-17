/*************************************************************************
                           Attribute  -  description
                             -------------------
    début                : 16/02/2025
    copyright            : (C) 2025 par Ewan
    e-mail               : ---
*************************************************************************/

//---------- Interface de la classe <Attribute> (fichier Attribute.h) ----------------
#if ! defined ( ATTRIBUTE_H )
#define ATTRIBUTE_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Xxx>
//
//
//------------------------------------------------------------------------

class Attribute
{
//----------------------------------------------------------------- PUBLIC

public:
//-------------------------------------------- Constructeurs - destructeur
    Attribute () = default; // For the unordered_map
    Attribute ( std::string unAttributeId, std::string unUnit, std::string uneDescription);
    // Mode d'emploi :
    //
    // Contrat :
    //


    std::string getAttributeId();

    std::string getUnit();

    std::string getDescription();


    
    virtual ~Attribute ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
        std::string attributeId;
        std::string unit;
        std::string description;
};

//-------------------------------- Autres définitions dépendantes de <Attribute>

#endif // ATTRIBUTE_H

