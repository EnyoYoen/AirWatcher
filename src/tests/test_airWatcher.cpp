#include <gtest/gtest.h>
#include "../services/AirWatcher.h"
#include <sstream>
#include <iostream>

// Voilà un exemple d'utilisation pour manipuler le menu
TEST(TestAirWatcher, affichageMenuConnexion)
{

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

TEST(TestAirWatcher, connexionAdmin)
{

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

TEST(TestAirWatcher, affichageMenu)
{
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

TEST(TestAirWatcher, banUser_UserExists)
{
    std::istringstream input("1\nadmin\nadmin\n8\n1\n9\n");

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
    EXPECT_NE(actualOutput.find("Bannir un utilisateur"), std::string::npos);
    EXPECT_NE(actualOutput.find("Choisissez un utilisateur"), std::string::npos);
    EXPECT_NE(actualOutput.find("1. User0"), std::string::npos);
    EXPECT_NE(actualOutput.find("2. User1"), std::string::npos);
    EXPECT_NE(actualOutput.find("Utilisateur User0 : banni"), std::string::npos);
}

TEST(TestAirWatcher, rechercheCapteursSimilaires_AucunTrouve)
{
    std::istringstream input("1\nadmin\nadmin\n5\n100\n9\n");

    // Sauvegarde cin original
    auto cin_backup = std::cin.rdbuf();

    // Redirige cin vers notre input simulé
    std::cin.rdbuf(input.rdbuf());

    // Capture la sortie standard
    std::ostringstream output;
    auto cout_backup = std::cout.rdbuf();
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
    EXPECT_NE(actualOutput.find("Recherche de capteurs similaires"), std::string::npos);
    EXPECT_NE(actualOutput.find("Choisissez un capteur"), std::string::npos);
    EXPECT_NE(actualOutput.find("100. Sensor56"), std::string::npos);
    EXPECT_NE(actualOutput.find("Aucun capteur similaire trouv"), std::string::npos);
}

TEST(TestAirWatcher, rechercheCapteursSimilaires_Trouve)
{
    std::istringstream input("1\nadmin\nadmin\n5\n99\n9\n");

    // Sauvegarde cin original
    auto cin_backup = std::cin.rdbuf();

    // Redirige cin vers notre input simulé
    std::cin.rdbuf(input.rdbuf());

    // Capture la sortie standard
    std::ostringstream output;
    auto cout_backup = std::cout.rdbuf();
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
    EXPECT_NE(actualOutput.find("Recherche de capteurs similaires"), std::string::npos);
    EXPECT_NE(actualOutput.find("Choisissez un capteur"), std::string::npos);
    EXPECT_NE(actualOutput.find("Capteurs similaires : "), std::string::npos);
    EXPECT_NE(actualOutput.find("Sensor1 | Lat: 44 | Lon: -0.3 | Fiable"), std::string::npos);
}

TEST(TestAirWatcher, verifierCapteurEnPanne)
{
    std::istringstream input("1\nadmin\nadmin\n6\n100\n9\n");

    // Sauvegarde cin original
    auto cin_backup = std::cin.rdbuf();

    // Redirige cin vers notre input simulé
    std::cin.rdbuf(input.rdbuf());

    // Capture la sortie standard
    std::ostringstream output;
    auto cout_backup = std::cout.rdbuf();
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
    EXPECT_NE(actualOutput.find("Vérification des capteurs en panne"), std::string::npos);
    EXPECT_NE(actualOutput.find("Choisissez un capteur"), std::string::npos);
    EXPECT_NE(actualOutput.find("100. Sensor56"), std::string::npos);
    EXPECT_NE(actualOutput.find("Capteur Sensor56 : en panne"), std::string::npos);
    EXPECT_NE(actualOutput.find("Sensor56 | Lat: 46 | Lon: 3.2 | Fiable"), std::string::npos);
}

TEST(TestAirWatcher, verifierCapteurEnPanne_Fonctionnel)
{
    std::istringstream input("1\nadmin\nadmin\n6\n99\n9\n");

    // Sauvegarde cin original
    auto cin_backup = std::cin.rdbuf();

    // Redirige cin vers notre input simulé
    std::cin.rdbuf(input.rdbuf());

    // Capture la sortie standard
    std::ostringstream output;
    auto cout_backup = std::cout.rdbuf();
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
    EXPECT_NE(actualOutput.find("Vérification des capteurs en panne"), std::string::npos);
    EXPECT_NE(actualOutput.find("Choisissez un capteur"), std::string::npos);
    EXPECT_NE(actualOutput.find("99. Sensor10"), std::string::npos);
    EXPECT_NE(actualOutput.find("Capteur Sensor10 : fonctionnel"), std::string::npos);
    EXPECT_NE(actualOutput.find("Sensor10 | Lat: 44.4 | Lon: -1 | Fiable"), std::string::npos);
}

TEST(TestAirWatcher, verifierCapteursEnPanne_Liste)
{
    std::istringstream input("1\nadmin\nadmin\n7\n9\n");

    // Sauvegarde cin original
    auto cin_backup = std::cin.rdbuf();

    // Redirige cin vers notre input simulé
    std::cin.rdbuf(input.rdbuf());

    // Capture la sortie standard
    std::ostringstream output;
    auto cout_backup = std::cout.rdbuf();
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
    EXPECT_NE(actualOutput.find("Capteurs en panne"), std::string::npos);
    EXPECT_NE(actualOutput.find("Sensor97 | Lat: 47.6 | Lon: 3.9 | Fiable"), std::string::npos);
    EXPECT_NE(actualOutput.find("Sensor96 | Lat: 47.6 | Lon: 3.2 | Fiable"), std::string::npos);
    EXPECT_NE(actualOutput.find("Sensor88 | Lat: 47.2 | Lon: 4.6 | Fiable"), std::string::npos);
    EXPECT_NE(actualOutput.find("Sensor85 | Lat: 47.2 | Lon: 2.5 | Fiable"), std::string::npos);
    EXPECT_NE(actualOutput.find("Sensor78 | Lat: 46.8 | Lon: 4.6 | Fiable"), std::string::npos);
    EXPECT_NE(actualOutput.find("Sensor77 | Lat: 46.8 | Lon: 3.9 | Fiable"), std::string::npos);
    EXPECT_NE(actualOutput.find("Sensor76 | Lat: 46.8 | Lon: 3.2 | Fiable"), std::string::npos);
    EXPECT_NE(actualOutput.find("Sensor68 | Lat: 46.4 | Lon: 4.6 | Fiable"), std::string::npos);
    EXPECT_NE(actualOutput.find("Sensor65 | Lat: 46.4 | Lon: 2.5 | Fiable"), std::string::npos);
    EXPECT_NE(actualOutput.find("Sensor57 | Lat: 46 | Lon: 3.9 | Fiable"), std::string::npos);
    EXPECT_NE(actualOutput.find("Sensor75 | Lat: 46.8 | Lon: 2.5 | Fiable"), std::string::npos);
    EXPECT_NE(actualOutput.find("Sensor87 | Lat: 47.2 | Lon: 3.9 | Fiable"), std::string::npos);
    EXPECT_NE(actualOutput.find("Sensor67 | Lat: 46.4 | Lon: 3.9 | Fiable"), std::string::npos);
    EXPECT_NE(actualOutput.find("Sensor47 | Lat: 45.6 | Lon: 3.9 | Fiable"), std::string::npos);
    EXPECT_NE(actualOutput.find("Sensor66 | Lat: 46.4 | Lon: 3.2 | Fiable"), std::string::npos);
    EXPECT_NE(actualOutput.find("Sensor86 | Lat: 47.2 | Lon: 3.2 | Fiable"), std::string::npos);
    EXPECT_NE(actualOutput.find("Sensor36 | Lat: 45.2 | Lon: 3.2 | Fiable"), std::string::npos);
    EXPECT_NE(actualOutput.find("Sensor58 | Lat: 46 | Lon: 4.6 | Fiable"), std::string::npos);
    EXPECT_NE(actualOutput.find("Sensor55 | Lat: 46 | Lon: 2.5 | Fiable"), std::string::npos);
    EXPECT_NE(actualOutput.find("Sensor56 | Lat: 46 | Lon: 3.2 | Fiable"), std::string::npos);
}