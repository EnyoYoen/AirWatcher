#include "DataLoader.h"

#include <fstream>
#include <sstream>

#include "DateTime.h"
#include "../model/Admin.h"

int DataLoader::loadSensors(unordered_map<string, Sensor> &sensorList)
{
    // Implementation for loading sensors from CSV file
    // Open the CSV file, read each line, parse the data, and populate the sensorList
    // Return 0 on success, non-zero on failure

    ifstream file("5_projet_dataset/sensors.csv");
    if (!file.is_open())
    {
        return FILE_ERROR; // Failed to open file
    }

    string line;
    while (getline(file, line))
    {
        istringstream ss(line);
        string sensorId, latitudeStr, longitudeStr;
        if (getline(ss, sensorId, ';') && getline(ss, latitudeStr, ';') && getline(ss, longitudeStr))
        {
            double latitude;
            double longitude;
            try
            {
                latitude = stod(latitudeStr);
                longitude = stod(longitudeStr);
            }
            catch (...)
            {
                return CONVERT_ERROR; // Failed to convert latitude/longitude to double
            }
            Sensor sensor(sensorId, latitude, longitude);
            sensorList[sensorId] = sensor;
        }
        else
        {
            return PARSE_ERROR; // Failed to parse line
        }
    }
    file.close();
    return NO_ERROR;
}

int DataLoader::loadMeasurements(unordered_map<string, vector<Measurement>> &measurements, unordered_map<string, Attribute> &attributes)
{
    // Implementation for loading measurements from CSV file
    // Open the CSV file, read each line, parse the data, and populate the measurementList
    // Return 0 on success, non-zero on failure

    int result = loadAttributes(attributes);
    if (result != NO_ERROR)
    {
        return result; // Failed to load attributes
    }

    ifstream file("5_projet_dataset/measurements.csv");
    if (!file.is_open())
    {
        return FILE_ERROR; // Failed to open file
    }

    string line;
    while (getline(file, line))
    {
        istringstream ss(line);
        string timestampStr, sensorId, attributeId, valueStr;
        if (getline(ss, timestampStr, ';') && getline(ss, sensorId, ';') && getline(ss, attributeId, ';') && getline(ss, valueStr))
        {
            double value;
            time_t timestamp = parseDateTime(timestampStr.c_str(), "%Y-%m-%d %H:%M:%S");
            if (timestamp == -1)
            {
                return CONVERT_ERROR; // Failed to convert timestamp
            }
            try
            {
                value = stod(valueStr);
            }
            catch (...)
            {
                return CONVERT_ERROR; // Failed to convert value to double
            }
            if (attributes.find(attributeId) == attributes.end())
            {
                return PARSE_ERROR; // Attribute not found
            }

            if (measurements.find(sensorId) == measurements.end())
            {
                measurements[sensorId] = vector<Measurement>();
            }

            Measurement measurement(timestamp, attributeId, value);
            measurements[sensorId].push_back(measurement);
        }
        else
        {
            return PARSE_ERROR; // Failed to parse line
        }
    }

    file.close();
    return NO_ERROR;
}

int DataLoader::loadProviders(unordered_map<string, Provider> &providerList, unordered_map<string, Cleaner> &cleanerList)
{
    // Implementation for loading providers from CSV file
    // Open the CSV file, read each line, parse the data, and populate the providerList
    // Return 0 on success, non-zero on failure

    unordered_map<string, list<string>> providersCleaners;
    unordered_map<string, Cleaner> cleaners;
    int result = loadCleaners(cleaners);
    if (result != NO_ERROR)
    {
        return result; // Failed to load cleaners
    }

    ifstream file("5_projet_dataset/providers.csv");
    if (!file.is_open())
    {
        return FILE_ERROR; // Failed to open file
    }

    string line;
    while (getline(file, line))
    {
        istringstream ss(line);
        string providerId, cleanerId;
        if (getline(ss, providerId, ';') && getline(ss, cleanerId))
        {
            if (providersCleaners.find(providerId) == providersCleaners.end())
            {
                providersCleaners[providerId] = list<string>();
            }
            providersCleaners[providerId].push_back(cleanerId);
        }
        else
        {
            return PARSE_ERROR; // Failed to parse line
        }
    }
    file.close();

    for (auto &pair : providersCleaners)
    {
        string providerId = pair.first;
        list<string> &cleanerIds = pair.second;

        Provider provider(providerId);
        for (const string &cleanerId : cleanerIds)
        {
            auto it = cleaners.find(cleanerId);
            if (it != cleaners.end())
            {
                provider.addCleaner(it->second);
            }
            else
            {
                // Cleaner not found
            }
        }
        providerList[providerId] = provider;
    }
    for (auto &pair : cleaners)
    {
        cleanerList[pair.first] = pair.second;
    }

    return NO_ERROR;
}

int DataLoader::loadUsers(unordered_map<string, User> &userList, unordered_map<string, PrivateUser> &privateUserList)
{
    // Implementation for loading users from CSV file
    // Open the CSV file, read each line, parse the data, and populate the userList
    // Return 0 on success, non-zero on failure

    unordered_map<string, list<string>> usersSensors;

    ifstream file("5_projet_dataset/users.csv");
    if (!file.is_open())
    {
        return FILE_ERROR; // Failed to open file
    }

    string line;
    while (getline(file, line))
    {
        istringstream ss(line);
        string userId, sensorId;
        if (getline(ss, userId, ';') && getline(ss, sensorId))
        {
            if (usersSensors.find(userId) == usersSensors.end())
            {
                usersSensors[userId] = list<string>();
            }
            usersSensors[userId].push_back(sensorId);
        }
        else
        {
            return PARSE_ERROR; // Failed to parse line
        }
    }
    file.close();

    for (const auto &pair : usersSensors)
    {
        const string &userId = pair.first;
        const list<string> &sensorIds = pair.second;

        for (const string &sensorId : sensorIds)
        {
            PrivateUser user(userId);
            for (const string &sensorId : sensorIds)
            {
                user.addSensor(sensorId);
            }
            userList[user.getUserId()] = user;
            privateUserList[user.getUserId()] = user;
        }
    }

    // Add Admin user
    Admin admin;
    userList[admin.getUserId()] = admin;

    return NO_ERROR;
}

// Private methods

int DataLoader::loadAttributes(unordered_map<string, Attribute> &attributes)
{
    // Implementation for loading attributes from CSV file
    // Open the CSV file, read each line, parse the data, and populate the attributeList
    // Return 0 on success, non-zero on failure

    ifstream file("5_projet_dataset/attributes.csv");
    if (!file.is_open())
    {
        return 1; // Failed to open file
    }

    string line;
    while (getline(file, line))
    {
        istringstream ss(line);
        string attributeId, unit, description;
        if (getline(ss, attributeId, ';') && getline(ss, unit, ';') && getline(ss, description))
        {
            Attribute attribute(attributeId, unit, description);
            attributes[attributeId] = attribute;
        }
        else
        {
            return 2; // Failed to parse line
        }
    }
    file.close();
    return 0;
}

int DataLoader::loadCleaners(unordered_map<string, Cleaner> &cleaners)
{
    // Implementation for loading cleaners from CSV file
    // Open the CSV file, read each line, parse the data, and populate the cleanerList
    // Return 0 on success, non-zero on failure

    ifstream file("5_projet_dataset/cleaners.csv");
    if (!file.is_open())
    {
        return FILE_ERROR; // Failed to open file
    }

    string line;
    while (getline(file, line))
    {
        istringstream ss(line);
        string cleanerId, latitudeStr, longitudeStr, startTimeStr, stopTimeStr;
        if (getline(ss, cleanerId, ';') && getline(ss, latitudeStr, ';') && getline(ss, longitudeStr, ';') && getline(ss, startTimeStr, ';') && getline(ss, stopTimeStr))
        {
            double latitude;
            double longitude;
            time_t startTime = parseDateTime(startTimeStr.c_str(), "%Y-%m-%d %H:%M:%S");
            time_t stopTime = parseDateTime(stopTimeStr.c_str(), "%Y-%m-%d %H:%M:%S");
            if (startTime == -1 || stopTime == -1)
            {
                return CONVERT_ERROR; // Failed to convert start/stop time
            }
            try
            {
                latitude = stod(latitudeStr);
                longitude = stod(longitudeStr);
            }
            catch (...)
            {
                return CONVERT_ERROR; // Failed to convert latitude/longitude
            }
            Cleaner cleaner(cleanerId, latitude, longitude, startTime, stopTime);
            cleaners[cleanerId] = cleaner;
        }
        else
        {
            return PARSE_ERROR; // Failed to parse line
        }
    }
    file.close();
    return NO_ERROR;
}