/*************************************************************************
                           DataLoader  -  Static data loader
                             -------------------
    début                : 16/5/2025
    copyright            : (C) 2025 par Garoux, Hequet, McCurdy, Lafon de la Laurencie, Peyrot.
*************************************************************************/

#if !defined(DATALOADER_H)
#define DATALOADER_H

#include "../model/Sensor.h"
#include "../model/Measurement.h"
#include "../model/User.h"
#include "../model/PrivateUser.h"
#include "../model/Admin.h"
#include "../model/Provider.h"
#include "../model/Cleaner.h"
#include "../model/Attribute.h"

#include <list>
#include <vector>
#include <unordered_map>

using namespace std;

class DataLoader
{
public:
    inline static const string sensorsPath = "5_projet_dataset/sensors.csv";
    inline static const string measurementsPath = "5_projet_dataset/measurements.csv";
    inline static const string providersPath = "5_projet_dataset/providers.csv";
    inline static const string usersPath = "5_projet_dataset/users.csv";
    inline static const string attributesPath = "5_projet_dataset/attributes.csv";
    inline static const string cleanersPath = "5_projet_dataset/cleaners.csv";

    // Load data from CSV files into the respective lists
    // The static methods are in the form of int load<Type>(list<Type>& list)
    // where int is the return code (0 for success, non zero for failure)
    static int loadSensors(unordered_map<string, Sensor> &sensorList, string filename = sensorsPath);
    static int loadMeasurements(unordered_map<string, vector<Measurement>> &measurements, unordered_map<string, Attribute> &attributes, string filenameMeasurements = measurementsPath, string filenameAttributes = attributesPath);
    static int loadProviders(unordered_map<string, Provider> &providerList, unordered_map<string, Cleaner> &cleanerList, string filenameProviders = providersPath, string filenameCleaners = cleanersPath);
    static int loadUsers(unordered_map<string, User> &userList, unordered_map<string, PrivateUser> &privateUserList, string filename = usersPath);
    static int loadAdmins(unordered_map<string, User> &userList, unordered_map<string, Admin> &adminList);

    enum LoadError
    {
        NO_ERROR = 0,
        FILE_ERROR = 1,
        PARSE_ERROR = 2,
        CONVERT_ERROR = 3
    };

private:
    DataLoader(); // Prevent instantiation of this class
    ~DataLoader();

    static int loadAttributes(unordered_map<string, Attribute> &attributes, string filename = attributesPath);
    static int loadCleaners(unordered_map<string, Cleaner> &cleanerList, string filename = cleanersPath);
};

#endif // DATALOADER_H