/*************************************************************************
                           Measurement - represents a sensor measurement  
                             -------------------
    début                : 16/05/2025
    copyright            : (C) 2025 par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Xxx> (fichier Xxx.h) ----------------
#ifndef MEASUREMENT_H 
#define MEASUREMENT_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

class Measurement 
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques
    std::string GetAttributeAsString() const;
    float getValue() const;
    std::string getTimestamp() const;

//-------------------------------------------- Constructeurs - destructeur
    Measurement(const std::string& timestamp, const Atrribute& attriubute, float value);
    Measurement(const Measurement& other);
    ~Measurement();

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    std::string timestamp;
    Attribute attribute;
    float value;
};

//-------------------------------- Autres définitions dépendantes de <Xxx>

#endif // MEASUREMENT_H
