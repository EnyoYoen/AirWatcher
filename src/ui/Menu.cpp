#include "Menu.h"

#include <iostream>

Menu::Menu(const Menu &unMenu) {

}

Menu::Menu() : logStream(nullptr) {

}

Menu &Menu::operator=(const Menu &unMenu) {
    if (this != &unMenu) {
        
    }
    return *this;
}

// Méthodes pour afficher des informations

void Menu::printSimilarSensors(const list<Sensor>& sensors) {
    cout << "Capteurs similaires : " << endl;
    for (const auto& sensor : sensors) {
        printSensor(sensor);
    }
}

void Menu::printMalfunctionSensors(const list<Sensor>& sensors) {
    cout << "Capteurs en panne : " << endl;
    for (const auto& sensor : sensors) {
        printSensor(sensor);
    }
}

void Menu::printUnreliableSensors(const list<Sensor>& sensors) {
    cout << "Capteurs non fiables : " << endl;
    for (const auto& sensor : sensors) {
        printSensor(sensor);
    }
}

// Méthodes de log

void Menu::setLogStream(ostream *stream) {
    logStream = stream;
}

void Menu::debug(const string& message) {
    if (logStream) {
        *logStream << "[DEBUG] " << message << endl;
    }
}

void Menu::error(const string& message) {
    if (logStream) {
        *logStream << "[ERROR] " << message << endl;
    }
}


// Protected

void Menu::printSensor(const Sensor& sensor) {
    cout << sensor.getSensorId() << " | Lat: " << sensor.getLatitude() << " | Lon: " << sensor.getLongitude() << " | " << (sensor.isReliable() ? "Fiable" : "Non fiable") << endl;
}

void Menu::printCleaner(const Cleaner& cleaner) {
    time_t startTime = cleaner.getStartTime();
    time_t stopTime = cleaner.getStopTime();
    cout << cleaner.getCleanerId() << " | Lat: " << cleaner.getLatitude() << " | Lon: " << cleaner.getLongitude() << " | Start: " << ctime(&startTime) << " | Stop: " << ctime(&stopTime) << endl;
}

void Menu::printUser(const User& user) {
    cout << user.getUserId() << endl;
}

string Menu::chooseSensorSubMenu(const list<Sensor>& sensors) {
    cout << "Choisissez un capteur : " << endl;
    int i = 1;
    for (const auto& sensor : sensors) {
        cout << i++ << ". ";
        printSensor(sensor);
    }
    
    int choice;
    do {
        cin >> choice;
    } while (choice < 1 || choice > sensors.size() || cin.fail());
    cin.clear();

    auto it = sensors.begin();
    advance(it, choice - 1);
    return it->getSensorId();
}

string Menu::chooseCleanerSubMenu(const list<Cleaner>& cleaners) {
    cout << "Choisissez un cleaner : " << endl;
    int i = 1;
    for (const auto& cleaner : cleaners) {
        cout << i++ << ". ";
        printCleaner(cleaner);
    }
    
    int choice;
    do {
        cin >> choice;
    } while (choice < 1 || choice > cleaners.size() || cin.fail());
    cin.clear();

    auto it = cleaners.begin();
    advance(it, choice - 1);
    return it->getCleanerId();
}

string Menu::chooseUserSubMenu(const list<User>& users) {
    cout << "Choisissez un utilisateur : " << endl;
    int i = 1;
    for (const auto& user : users) {
        cout << i++ << ". ";
        printUser(user);
    }
    
    int choice;
    do {
        cin >> choice;
    } while (choice < 1 || choice > users.size() || cin.fail());
    cin.clear();

    auto it = users.begin();
    advance(it, choice - 1);
    return it->getUserId();
}