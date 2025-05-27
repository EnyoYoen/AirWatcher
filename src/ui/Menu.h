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

#include "../model/Sensor.h"
#include "../model/Cleaner.h"
#include "../model/User.h"

using namespace std;

enum MenuChoice
{
    LOGIN_MENU = 1,
    AIR_QUALITY_MENU,
    POINT_AIR_QUALITY_MENU,
    CLEANER_IMPACT_MENU,
    FIND_SIMILAR_SENSORS_MENU,
    CHECK_MALFUNCTION_MENU,
    CHECK_UNRELIABLE_MENU,
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
    string cleanerImpactMenu(const list<Cleaner> &cleaners);

    // Menu de recherche de capteurs similaires, qui demande quel capteur on veut
    // et retourne l'id du capteur
    string findSimilarSensorsMenu(const list<Sensor> &sensors);

    // Menu de recherche de capteurs en panne, qui demande quel capteur on veut
    // et retourne l'id du capteur
    string checkMalfunctionMenu(const list<Sensor> &sensors);

    // Menu de recherche de capteurs non fiables, qui demande quel capteur on veut
    // et retourne l'id du capteur
    string checkUnreliableMenu(const list<Sensor> &sensors, const list<User> &users);

    /**********************************************
        Méthodes pour afficher des informations
    ***********************************************/
    void printSimilarSensors(const list<Sensor> &sensors);
    void printMalfunctionSensors(const list<Sensor> &sensors);
    void printUnreliableSensors(const list<Sensor> &sensors);

    /************************************************
            Méthodes pour log des messages
        (dans un stream spécifié par setLogStream)
    ************************************************/
    void setLogStream(ostream *stream);
    void debug(const string &message);
    void error(const string &message);

protected:
    string chooseSensorSubMenu(const list<Sensor> &sensors);
    string chooseCleanerSubMenu(const list<Cleaner> &cleaners);
    string chooseUserSubMenu(const list<User> &users);

    ostream *logStream;
};

#endif // MENU_H
