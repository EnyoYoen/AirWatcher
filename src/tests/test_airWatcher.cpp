#include <gtest/gtest.h>
#include "../services/AirWatcher.h"
#include <sstream>
#include <iostream>

// Voilà un exemple d'utilisation pour manipuler le menu
TEST(TestAirWatcher, quitterDirectement) {
    
    std::istringstream input("2\n");

    // Sauvegarde cin original
    auto cin_backup = std::cin.rdbuf();

    // Redirige cin vers notre input simulé
    std::cin.rdbuf(input.rdbuf());

    // Appelle la fonction qui attend l'entrée standard
    AirWatcher aw;

    // Restaure cin
    std::cin.rdbuf(cin_backup);
}