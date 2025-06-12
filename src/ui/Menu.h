/*************************************************************************
                           Menu  -  description
                             -------------------
    début                : 16/5/2025
    copyright            : (C) 2025 par Garoux, Hequet, McCurdy, Lafon de la Laurencie, Peyrot.
*************************************************************************/

#if !defined(MENU_H)
#define MENU_H

#include <string>
#include <ostream>
#include <list>
#include <tuple>
#include <unordered_map>

#include "../model/Sensor.h"
#include "../model/Cleaner.h"
#include "../model/User.h"
#include "../model/PrivateUser.h"

using namespace std;

enum MenuChoice
{
    LOGIN_MENU = 1,
    AIR_QUALITY_MENU,
    POINT_AIR_QUALITY_MENU,
    CLEANER_IMPACT_MENU,
    FIND_SIMILAR_SENSORS_MENU,
    CHECK_ONE_MALFUNCTION_MENU,
    CHECK_MALFUNCTION_MENU,
    BAN_USER_MENU,
    EXIT
};

enum MenuRights
{
    NOT_LOGGED_IN = 0,
    PRIVATE_USER,
    ADMIN
};

class Menu
{

public:
    Menu &operator=(const Menu &unMenu);

    Menu(const Menu &unMenu);
    Menu();
    virtual ~Menu();

    /***************************************************
        Méthodes (bloquante) pour afficher les menus
    ***************************************************/
    // Menu principal, qui permet de choisir entre les différents sous-menus et retourne le choix de l'utilisateur
    MenuChoice mainMenu(MenuRights rights);

    // Menu de connexion, qui demande le nom d'utilisateur et le mot de passe (et les retourne)
    pair<string, string> loginMenu();

    // Menu de qualité de l'air, qui demande la date de début, la date de fin, les coordonnées et le rayon de recherche
    // et retourne un tuple contenant ces informations
    tuple<time_t, time_t, double, double, double> airQualityMenu();

    // Menu de qualité de l'air, qui demande les coordonnées et la date de mesure
    tuple<double, double, time_t> pointAirQualityMenu();

    // Menu d'impact des cleaners, qui demande quel cleaner on veut mesurer l'impact
    // et retourne l'id du cleaner
    string cleanerImpactMenu(const unordered_map<string, Cleaner> &cleaners);

    // Menu de recherche de capteurs similaires, qui demande quel capteur on veut
    // et retourne l'id du capteur
    string findSimilarSensorsMenu(const unordered_map<string, Sensor> &sensors);

    // Menu de recherche de capteurs en panne, qui demande quel capteur on veut
    // et retourne l'id du capteur
    string checkOneMalfunctionMenu(const unordered_map<string, Sensor> &sensors);

    // Menu de bannissement d'un utilisateur, qui demande quel utilisateur on veut bannir
    // et retourne l'id de l'utilisateur
    string banUserMenu(const unordered_map<string, PrivateUser> &users);

    /**********************************************
        Méthodes pour afficher des informations
    ***********************************************/
    void printAirQuality(float airQuality);
    void printSimilarSensors(const list<Sensor> &sensors);
    void printOneMalfunctionSensor(const Sensor &sensor, bool isMalfunctioning);
    void printMalfunctionSensors(const list<Sensor> &sensors);
    void printUnreliableSensors(const list<Sensor> &sensors);
    void printBannedUser(const User &user, bool isBanned);
    void printCleanerImpact(const Cleaner &cleaner, bool isValid, float * impact);

    /************************************************
            Méthodes pour log des messages
        (dans un stream spécifié par setLogStream)
    ************************************************/
    void setLogStream(ostream *stream);
    void debug(const string &message) const;
    void error(const string &message) const;

protected:
    string chooseSensorSubMenu(const unordered_map<string, Sensor> &sensors);
    string chooseCleanerSubMenu(const unordered_map<string, Cleaner> &cleaners);
    string chooseUserSubMenu(const unordered_map<string, PrivateUser> &users);

    ostream *logStream;
};

#endif // MENU_H
