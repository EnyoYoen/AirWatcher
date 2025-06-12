#include <gtest/gtest.h>
#include "../services/AirWatcher.h"
#include <sstream>
#include <iostream>

// Voilà un exemple d'utilisation pour manipuler le menu
TEST(TestAirWatcher, affichageMenuConnexion) {
    
    std::istringstream input("2\n");

    // Sauvegarde cin original
    auto cin_backup = std::cin.rdbuf();

    // Redirige cin vers notre input simulé
    std::cin.rdbuf(input.rdbuf());

    // Capture la sortie standard
    std::ostringstream output;
    auto cout_backup = std::cout.rdbuf(); // Sauvegarde std::cout
    std::cout.rdbuf(output.rdbuf()); 

    // Appelle la fonction qui attend l'entrée standard
    AirWatcher aw;

    // Restaure cin
    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);

    std::string actualOutput = output.str();
    EXPECT_NE(actualOutput.find("1. Connexion"), std::string::npos); 
    EXPECT_NE(actualOutput.find("2. Quitter"), std::string::npos); 
}

TEST(TestAirWatcher, connexionAdmin) {
    
    std::istringstream input("1\nadmin\nadmin\n9\n");

    // Sauvegarde cin original
    auto cin_backup = std::cin.rdbuf();

    // Redirige cin vers notre input simulé
    std::cin.rdbuf(input.rdbuf());

    // Capture la sortie standard
    std::ostringstream output;
    auto cout_backup = std::cout.rdbuf(); // Sauvegarde std::cout
    std::cout.rdbuf(output.rdbuf()); 

    // Appelle la fonction qui attend l'entrée standard
    AirWatcher aw;

    // Restaure cin & cout
    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);

    std::string actualOutput = output.str();
    EXPECT_NE(actualOutput.find("Login successful for user: admin"), std::string::npos);
}

TEST(TestAirWatcher, affichageMenu) {
    
    std::istringstream input("1\nadmin\nadmin\n9\n");

    // Sauvegarde cin original
    auto cin_backup = std::cin.rdbuf();

    // Redirige cin vers notre input simulé
    std::cin.rdbuf(input.rdbuf());

    // Capture la sortie standard
    std::ostringstream output;
    auto cout_backup = std::cout.rdbuf(); // Sauvegarde std::cout
    std::cout.rdbuf(output.rdbuf()); 

    // Appelle la fonction qui attend l'entrée standard
    AirWatcher aw;

    // Restaure cin & cout
    std::cin.rdbuf(cin_backup);
    std::cout.rdbuf(cout_backup);

    std::string actualOutput = output.str();
    EXPECT_NE(actualOutput.find("1. Connexion"), std::string::npos); 
    EXPECT_NE(actualOutput.find("2. Qualité de l'air"), std::string::npos); 
    EXPECT_NE(actualOutput.find("3. Qualité de l'air à un point"), std::string::npos); 
    EXPECT_NE(actualOutput.find("4. Impact des cleaners"), std::string::npos); 
    EXPECT_NE(actualOutput.find("5. Rechercher des capteurs similaires"), std::string::npos); 
    EXPECT_NE(actualOutput.find("6. Vérifier un capteur en panne"), std::string::npos); 
    EXPECT_NE(actualOutput.find("7. Vérifier les capteurs en panne"), std::string::npos); 
    EXPECT_NE(actualOutput.find("8. Bannir un utilisateur"), std::string::npos); 
    EXPECT_NE(actualOutput.find("9. Quitter"), std::string::npos); 
}