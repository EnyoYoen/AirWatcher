#include <gtest/gtest.h>
#include "../utils/DataLoader.h"

//TODO : inclure

TEST(TestDataLoader, loadSensorsOK) {
    
    list<Sensor> sensorList;
    int res = DataLoader::loadSensors(sensorList);

    // CSV won't be updated, the size is fixed
    const int lengthSensorsCSV = 100;

    EXPECT_EQ(res, DataLoader::NO_ERROR);
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

TEST(TestDataLoader, loadProvidersOK) {

    list<Provider> providerList;
    list<Cleaner> cleanerList;
    int res = DataLoader::loadProviders(providerList, cleanerList);

    EXPECT_EQ(res, DataLoader::NO_ERROR);

    // CSV won't be updated, the size is fixed
    const int lengthProvidersCSV = 2;

    EXPECT_EQ(providerList.size(), lengthProvidersCSV);

    // CSV won't be updated, the size is fixed
    const int lengthCleanersCSV = 2;

    EXPECT_EQ(cleanerList.size(), lengthCleanersCSV);
}

TEST(TestDataLoader, loadUsersOK) {
    
    list<User> userList;
    int res = DataLoader::loadUsers(userList);

    EXPECT_EQ(res, DataLoader::NO_ERROR);

    // CSV won't be updated, the size is fixed
    const int lengthUsersCSV = 2;

    EXPECT_EQ(userList.size(), lengthUsersCSV);
}