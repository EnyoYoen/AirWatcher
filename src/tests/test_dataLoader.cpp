#include <gtest/gtest.h>
#include "../utils/DataLoader.h"

// Constantes utiles
static const string pathEmptyCSV = "5_projet_dataset/fakeCSV/empty.csv";

//LoadSensor
TEST(TestDataLoader, loadSensorsOK) {

    unordered_map<string, Sensor> sensorList;
    
    int res = DataLoader::loadSensors(sensorList);

    // CSV won't be updated, the size is fixed
    const int lengthSensorsCSV = 100;

    EXPECT_EQ(res, DataLoader::NO_ERROR);
    EXPECT_EQ(sensorList.size(), lengthSensorsCSV);
}

TEST(TestDataLoader, loadSensorsEmptyCSV) {

    unordered_map<string, Sensor> sensorList;
    
    int res = DataLoader::loadSensors(sensorList, pathEmptyCSV);

    // CSV won't be updated, the size is fixed
    const int lengthSensorsCSV = 0;

    EXPECT_EQ(res, DataLoader::NO_ERROR);
    EXPECT_EQ(sensorList.size(), lengthSensorsCSV);
}

TEST(TestDataLoader, loadSensorsBadFormat) {

    unordered_map<string, Sensor> sensorList;
    
    int res = DataLoader::loadSensors(sensorList, "5_projet_dataset/fakeCSV/badSensors.csv");

    // CSV won't be updated, the size is fixed
    const int lengthSensorsCSV = 0;

    EXPECT_EQ(res, DataLoader::PARSE_ERROR);
    EXPECT_EQ(sensorList.size(), lengthSensorsCSV);
}

TEST(TestDataLoader, loadMeasurementsOK) {
    
    unordered_map<string, vector<Measurement>> measurements;
    unordered_map<string, Attribute> attributes;
    int res = DataLoader::loadMeasurements(measurements, attributes);

    EXPECT_EQ(res, DataLoader::NO_ERROR);

    // CSV won't be updated, the size is fixed
    const int lengthSensorsCSV = 100;

    // Each sensor has its own vector of measurements 
    EXPECT_EQ(measurements.size(), lengthSensorsCSV);

    // CSV won't be updated, the size is fixed
    const int lengthMeasurementsCSV = 146000;
    int cptMeasurements = 0;
    for (const auto& [key, vec] : measurements) {
        cptMeasurements += vec.size();
    }
    EXPECT_EQ(cptMeasurements, lengthMeasurementsCSV);

    const int nbAttributes = 5;
    EXPECT_EQ(attributes.size(), nbAttributes);
}

TEST(TestDataLoader, loadMeasurementsEmpty) {
    
    unordered_map<string, vector<Measurement>> measurements;
    unordered_map<string, Attribute> attributes;
    int res = DataLoader::loadMeasurements(measurements, attributes, pathEmptyCSV, pathEmptyCSV);

    EXPECT_EQ(res, DataLoader::NO_ERROR);

    // CSV won't be updated, the size is fixed
    const int lengthSensorsCSV = 0;

    // Each sensor has its own vector of measurements 
    EXPECT_EQ(measurements.size(), lengthSensorsCSV);

    // CSV won't be updated, the size is fixed
    const int lengthMeasurementsCSV = 0;
    int cptMeasurements = 0;
    for (const auto& [key, vec] : measurements) {
        cptMeasurements += vec.size();
    }
    EXPECT_EQ(cptMeasurements, lengthMeasurementsCSV);

    const int nbAttributes = 0;
    EXPECT_EQ(attributes.size(), nbAttributes);
}


TEST(TestDataLoader, loadMeasurementsBadFormat) {
    
    unordered_map<string, vector<Measurement>> measurements;
    unordered_map<string, Attribute> attributes;
    int res = DataLoader::loadMeasurements(measurements, attributes, "5_projet_dataset/fakeCSV/badMeasurements.csv", "5_projet_dataset/fakeCSV/badAttributes.csv");

    EXPECT_EQ(res, DataLoader::PARSE_ERROR);

    // CSV won't be updated, the size is fixed
    const int lengthSensorsCSV = 0;

    // Each sensor has its own vector of measurements 
    EXPECT_EQ(measurements.size(), lengthSensorsCSV);

    // CSV won't be updated, the size is fixed
    const int lengthMeasurementsCSV = 0;
    int cptMeasurements = 0;
    for (const auto& [key, vec] : measurements) {
        cptMeasurements += vec.size();
    }
    EXPECT_EQ(cptMeasurements, lengthMeasurementsCSV);

    const int nbAttributes = 0;
    EXPECT_EQ(attributes.size(), nbAttributes);
}

TEST(TestDataLoader, loadProvidersOK) {

    unordered_map<string, Provider> providerList;
    unordered_map<string, Cleaner> cleanerList;

    int res = DataLoader::loadProviders(providerList, cleanerList);

    EXPECT_EQ(res, DataLoader::NO_ERROR);

    // CSV won't be updated, the size is fixed
    const int lengthProvidersCSV = 2;

    EXPECT_EQ(providerList.size(), lengthProvidersCSV);

    // CSV won't be updated, the size is fixed
    const int lengthCleanersCSV = 2;

    EXPECT_EQ(cleanerList.size(), lengthCleanersCSV);
}

TEST(TestDataLoader, loadProvidersEmpty) {

    unordered_map<string, Provider> providerList;
    unordered_map<string, Cleaner> cleanerList;

    int res = DataLoader::loadProviders(providerList, cleanerList, pathEmptyCSV, pathEmptyCSV);

    EXPECT_EQ(res, DataLoader::NO_ERROR);

    // CSV won't be updated, the size is fixed
    const int lengthProvidersCSV = 0;

    EXPECT_EQ(providerList.size(), lengthProvidersCSV);

    // CSV won't be updated, the size is fixed
    const int lengthCleanersCSV = 0;

    EXPECT_EQ(cleanerList.size(), lengthCleanersCSV);
}

TEST(TestDataLoader, loadProvidersBadFormat) {

    unordered_map<string, Provider> providerList;
    unordered_map<string, Cleaner> cleanerList;

    int res = DataLoader::loadProviders(providerList, cleanerList, "5_projet_dataset/fakeCSV/badProviders.csv", "5_projet_dataset/fakeCSV/badCleaners.csv");

    EXPECT_EQ(res, DataLoader::PARSE_ERROR);

    // CSV won't be updated, the size is fixed
    const int lengthProvidersCSV = 0;

    EXPECT_EQ(providerList.size(), lengthProvidersCSV);

    // CSV won't be updated, the size is fixed
    const int lengthCleanersCSV = 0;

    EXPECT_EQ(cleanerList.size(), lengthCleanersCSV);
}

TEST(TestDataLoader, loadUsersOK) {

    unordered_map<string, User> userList; 
    unordered_map<string, PrivateUser> privateUserList;
    
    int res = DataLoader::loadUsers(userList, privateUserList);

    EXPECT_EQ(res, DataLoader::NO_ERROR);

    // CSV won't be updated, the size is fixed
    // 2 users + 1 admin
    const int lengthUsersCSV = 3;

    EXPECT_EQ(userList.size(), lengthUsersCSV);
}

TEST(TestDataLoader, loadUsersEmpty) {

    unordered_map<string, User> userList; 
    unordered_map<string, PrivateUser> privateUserList;
    
    int res = DataLoader::loadUsers(userList, privateUserList, pathEmptyCSV);

    EXPECT_EQ(res, DataLoader::NO_ERROR);

    // CSV won't be updated, the size is fixed
    // 0 user + 1 admin
    const int lengthUsersCSV = 1;

    EXPECT_EQ(userList.size(), lengthUsersCSV);
}

TEST(TestDataLoader, loadUsersBadFormat) {

    unordered_map<string, User> userList; 
    unordered_map<string, PrivateUser> privateUserList;
    
    int res = DataLoader::loadUsers(userList, privateUserList, "5_projet_dataset/fakeCSV/badUsers.csv");

    EXPECT_EQ(res, DataLoader::PARSE_ERROR);

    const int lengthUsersCSV = 0;

    EXPECT_EQ(userList.size(), lengthUsersCSV);
}
