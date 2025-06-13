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
    const vector<string> menuOptions = {
        "Connexion",
        "Qualité de l'air",
        "Qualité de l'air à un point",
        "Impact des cleaners",
        "Rechercher des capteurs similaires",
        "Vérifier un capteur en panne",
        "Vérifier les capteurs en panne",
        "Bannir un utilisateur",
        "Quitter"};

    int maxOptions = MenuRights::NOT_LOGGED_IN == rights ? 2 : MenuRights::PRIVATE_USER == rights ? 5
                                                                                                  : 9;

    int choice;
    cout << endl;
    cout << "Menu principal : " << endl;
    for (size_t i = 0; i < maxOptions - 1; ++i)
    {
        cout << i + 1 << ". " << menuOptions[i] << endl;
    }
    cout << maxOptions << ". " << menuOptions.back() << endl;
    cout << "Veuillez choisir une option (1-" << maxOptions << ") : ";

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
        invalidInput = choice < 1 || choice > maxOptions || cin.fail();
    } while (invalidInput);

    return static_cast<MenuChoice>(choice == maxOptions ? MenuChoice::EXIT : choice);
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
    std::getline(std::cin, startDate);

    try
    {
        startTime = parseDateTime(startDate.c_str(), "%Y-%m-%d %H:%M:%S");
    }
    catch (const invalid_argument &e)
    {
        cerr << "Erreur : Format de date invalide. Veuillez réessayer." << endl;
        startTime = 0; // Or handle appropriately
    }

    cout << "Date de fin (format : YYYY-MM-DD hh:mm:ss) : ";
    string endDate;

    std::getline(std::cin, endDate);

    try
    {
        endTime = parseDateTime(endDate.c_str(), "%Y-%m-%d %H:%M:%S");
    }
    catch (const invalid_argument &e)
    {
        cerr << "Erreur : Format de date invalide. Veuillez réessayer." << endl;
        endTime = 0; // Or handle appropriately
    }

    cout << "Latitude : ";
    cin >> latitude;

    cout << "Longitude : ";
    cin >> longitude;

    cout << "Rayon de recherche (en km) : ";
    cin >> radius;

    return make_tuple(startTime, endTime, radius, latitude, longitude);
}

tuple<double, double, time_t> Menu::pointAirQualityMenu()
{
    double latitude, longitude;
    time_t dateTime;

    cout << "Latitude : ";
    cin >> latitude;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Longitude : ";
    cin >> longitude;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Date de mesure (format : YYYY-MM-DD hh:mm:ss) : ";
    string dateString;
    cin >> dateString;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    dateTime = parseDateTime(dateString.c_str(), "%Y-%m-%d %H:%M:%S");

    return make_tuple(latitude, longitude, dateTime);
}

string Menu::cleanerImpactMenu(const unordered_map<string, Cleaner> &cleaners)
{
    cout << "Impact des cleaners" << endl;
    return chooseCleanerSubMenu(cleaners);
}

string Menu::findSimilarSensorsMenu(const unordered_map<string, Sensor> &sensors)
{
    cout << "Recherche de capteurs similaires" << endl;
    return chooseSensorSubMenu(sensors);
}

string Menu::checkOneMalfunctionMenu(const unordered_map<string, Sensor> &sensors)
{
    cout << "Vérification des capteurs en panne" << endl;
    return chooseSensorSubMenu(sensors);
}

string Menu::banUserMenu(const unordered_map<string, PrivateUser> &users)
{
    cout << "Bannir un utilisateur" << endl;
    return chooseUserSubMenu(users);
}

// Méthodes pour afficher des informations

void Menu::printAirQuality(float airQuality)
{
    if (airQuality == -1)
    {
        cout << "Aucune donnée de qualité de l'air disponible pour cette période." << endl;
    }
    else
    {
        cout << "Qualité de l'air moyenne : " << airQuality << endl;
    }
}

void Menu::printSimilarSensors(const list<Sensor> &sensors)
{
    cout << "Capteurs similaires : " << endl;
    for (const auto &sensor : sensors)
    {
        cout << sensor.toString() << endl;
    }
    if (sensors.empty())
    {
        cout << "Aucun capteur similaire trouvé." << endl;
    }
}

void Menu::printOneMalfunctionSensor(const Sensor &sensor, bool isMalfunctioning)
{
    cout << "Capteur " << sensor.getSensorId() << " : " << (isMalfunctioning ? "en panne" : "fonctionnel") << endl;
    cout << sensor.toString() << endl;
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

void Menu::printBannedUser(const PrivateUser &user, bool isBanned)
{
    cout << "Utilisateur " << user.getUserId() << " (" << user.getPoints() << " points) : " << (isBanned ? "banni" : "non banni") << endl;
}

void Menu::printCleanerImpact(const Cleaner &cleaner, bool isValid, float *impact)
{
    if (isValid)
    {
        cout << "Impact du cleaner " << cleaner.getCleanerId() << " a modifié de " << *impact << " % la zone avoisinante" << endl;
    }
    else
    {
        cout << "Le calcul de l'impact du cleaner " << cleaner.getCleanerId() << " a rencontré une erreur" << endl;
    }
}

void Menu::printInvalidCredentials()
{
    cout << "Identifiants invalides, veuillez réessayer." << endl;
}

// Méthodes de log

void Menu::setLogStream(ostream *stream)
{
    logStream = stream;
}

void Menu::debug(const string &message) const
{
    if (logStream)
    {
        *logStream << "[DEBUG] " << message << endl;
    }
}

void Menu::error(const string &message) const
{
    if (logStream)
    {
        *logStream << "[ERROR] " << message << endl;
    }
}

// Protected

string Menu::chooseSensorSubMenu(const unordered_map<string, Sensor> &sensors)
{
    cout << "Choisissez un capteur : " << endl;
    int i = 1;
    for (const auto &sensor : sensors)
    {
        cout << i++ << ". " << sensor.second.toString() << endl;
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
    return it->second.getSensorId();
}

string Menu::chooseCleanerSubMenu(const unordered_map<string, Cleaner> &cleaners)
{
    cout << "Choisissez un cleaner : " << endl;
    int i = 1;
    for (const auto &cleaner : cleaners)
    {
        cout << i++ << ". " << cleaner.second.toString() << endl;
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
    return it->second.getCleanerId();
}

string Menu::chooseUserSubMenu(const unordered_map<string, PrivateUser> &users)
{
    cout << "Choisissez un utilisateur : " << endl;
    cout << "0. Annuler" << endl;
    int i = 1;
    for (const auto &user : users)
    {
        cout << i++ << ". " << user.second.toString() << endl;
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
        invalidInput = choice < 0 || choice > users.size() || cin.fail();
    } while (invalidInput);

    if (choice == 0)
    {
        return string();
    }

    auto it = users.begin();
    advance(it, choice - 1);
    return it->second.getUserId();
}