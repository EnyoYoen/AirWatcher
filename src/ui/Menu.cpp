#include "Menu.h"

#include <iostream>

#include "../utils/DateTime.h"

Menu &Menu::operator=(const Menu &unMenu)
{
    if (this != &unMenu)
    {
    }
    return *this;
}

Menu::Menu(const Menu &unMenu)
{
}

Menu::Menu() : logStream(nullptr)
{
}

Menu::~Menu()
{
}

// Méthodes (bloquante) pour afficher les menus

MenuChoice Menu::mainMenu(MenuRights rights)
{
    int choice;
    cout << endl;
    cout << "Menu principal : " << endl;
    cout << "1. Connexion" << endl;
    cout << "2. Qualité de l'air" << endl;
    cout << "3. Qualité de l'air à un point" << endl;
    cout << "4. Impact des cleaners" << endl;
    cout << "5. Rechercher des capteurs similaires" << endl;
    cout << "6. Vérifier les capteurs en panne" << endl;
    cout << "7. Vérifier les capteurs non fiables" << endl;
    cout << "8. Quitter" << endl;

    bool invalidInput = false;
    do
    {
        if (invalidInput)
        {
            cout << "Choix invalide, veuillez réessayer." << endl;
        }
        cin >> choice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        invalidInput = choice < 1 || choice > 9 || cin.fail();
    } while (invalidInput);

    return static_cast<MenuChoice>(choice);
}

pair<string, string> Menu::loginMenu()
{
    string username, password;
    cout << "Nom d'utilisateur : ";
    cin >> username;
    cout << "Mot de passe : ";
    cin >> password;
    return make_pair(username, password);
}

tuple<time_t, time_t, double, double, double> Menu::airQualityMenu()
{
    time_t startTime, endTime;
    double latitude, longitude, radius;

    cout << "Date de début (format : YYYY-MM-DD hh:mm:ss) : ";
    string startDate;
    cin >> startDate;
    startTime = parseDateTime(startDate.c_str(), "%Y-%m-%d %H:%M:%S");

    cout << "Date de fin (format : YYYY-MM-DD) : ";
    string endDate;
    cin >> endDate;
    endTime = parseDateTime(endDate.c_str(), "%Y-%m-%d %H:%M:%S");

    cout << "Latitude : ";
    cin >> latitude;

    cout << "Longitude : ";
    cin >> longitude;

    cout << "Rayon de recherche (en km) : ";
    cin >> radius;

    return make_tuple(startTime, endTime, latitude, longitude, radius);
}

tuple<double, double, time_t> Menu::pointAirQualityMenu()
{
    double latitude, longitude;
    time_t dateTime;

    cout << "Latitude : ";
    cin >> latitude;

    cout << "Longitude : ";
    cin >> longitude;

    cout << "Date de mesure (format : YYYY-MM-DD hh:mm:ss) : ";
    string dateString;
    cin >> dateString;
    dateTime = parseDateTime(dateString.c_str(), "%Y-%m-%d %H:%M:%S");

    return make_tuple(latitude, longitude, dateTime);
}

string Menu::cleanerImpactMenu(const list<Cleaner> &cleaners)
{
    cout << "Impact des cleaners" << endl;
    return chooseCleanerSubMenu(cleaners);
}

string Menu::findSimilarSensorsMenu(const list<Sensor> &sensors)
{
    cout << "Recherche de capteurs similaires" << endl;
    return chooseSensorSubMenu(sensors);
}

string Menu::checkMalfunctionMenu(const list<Sensor> &sensors)
{
    cout << "Vérification des capteurs en panne" << endl;
    return chooseSensorSubMenu(sensors);
}

string Menu::checkUnreliableMenu(const list<Sensor> &sensors, const list<User> &users)
{
    cout << "Vérification des capteurs non fiables" << endl;
    return chooseSensorSubMenu(sensors);
}

// Méthodes pour afficher des informations

void Menu::printSimilarSensors(const list<Sensor> &sensors)
{
    cout << "Capteurs similaires : " << endl;
    for (const auto &sensor : sensors)
    {
        cout << sensor.toString() << endl;
    }
}

void Menu::printMalfunctionSensors(const list<Sensor> &sensors)
{
    cout << "Capteurs en panne : " << endl;
    for (const auto &sensor : sensors)
    {
        cout << sensor.toString() << endl;
    }
}

void Menu::printUnreliableSensors(const list<Sensor> &sensors)
{
    cout << "Capteurs non fiables : " << endl;
    for (const auto &sensor : sensors)
    {
        cout << sensor.toString() << endl;
    }
}

// Méthodes de log

void Menu::setLogStream(ostream *stream)
{
    logStream = stream;
}

void Menu::debug(const string &message)
{
    if (logStream)
    {
        *logStream << "[DEBUG] " << message << endl;
    }
}

void Menu::error(const string &message)
{
    if (logStream)
    {
        *logStream << "[ERROR] " << message << endl;
    }
}

// Protected

string Menu::chooseSensorSubMenu(const list<Sensor> &sensors)
{
    cout << "Choisissez un capteur : " << endl;
    int i = 1;
    for (const auto &sensor : sensors)
    {
        cout << i++ << ". " << sensor.toString() << endl;
    }

    int choice;
    bool invalidInput = false;
    do
    {
        if (invalidInput)
        {
            cout << "Choix invalide, veuillez réessayer." << endl;
        }
        cin >> choice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        invalidInput = choice < 1 || choice > sensors.size() || cin.fail();
    } while (invalidInput);

    auto it = sensors.begin();
    advance(it, choice - 1);
    return it->getSensorId();
}

string Menu::chooseCleanerSubMenu(const list<Cleaner> &cleaners)
{
    cout << "Choisissez un cleaner : " << endl;
    int i = 1;
    for (const auto &cleaner : cleaners)
    {
        cout << i++ << ". " << cleaner.toString() << endl;
    }

    int choice;
    bool invalidInput = false;
    do
    {
        if (invalidInput)
        {
            cout << "Choix invalide, veuillez réessayer." << endl;
        }
        cin >> choice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        invalidInput = choice < 1 || choice > cleaners.size() || cin.fail();
    } while (invalidInput);

    auto it = cleaners.begin();
    advance(it, choice - 1);
    return it->getCleanerId();
}

string Menu::chooseUserSubMenu(const list<User> &users)
{
    cout << "Choisissez un utilisateur : " << endl;
    int i = 1;
    for (const auto &user : users)
    {
        cout << i++ << ". " << user.toString() << endl;
    }

    int choice;
    bool invalidInput = false;
    do
    {
        if (invalidInput)
        {
            cout << "Choix invalide, veuillez réessayer." << endl;
        }
        cin >> choice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        invalidInput = choice < 1 || choice > users.size() || cin.fail();
    } while (invalidInput);

    auto it = users.begin();
    advance(it, choice - 1);
    return it->getUserId();
}