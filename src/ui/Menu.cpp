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