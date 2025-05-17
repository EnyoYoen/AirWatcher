#include "DataLoader.h"

#include <fstream>
#include <sstream>

#include "Provider.h"
#include "utils/DateTime.h"

int DataLoader::loadSensors(list<Sensor> &sensorList)
{
    // Implementation for loading sensors from CSV file
    // Open the CSV file, read each line, parse the data, and populate the sensorList
    // Return 0 on success, non-zero on failure

    std::ifstream file("5_projet_dataset/sensors.csv");
    if (!file.is_open())
    {
        return FILE_ERROR; // Failed to open file
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string sensorId, latitudeStr, longitudeStr;
        if (std::getline(ss, sensorId, ';') && std::getline(ss, latitudeStr) && std::getline(ss, longitudeStr))
        {
            double latitude;
            double longitude;
            try
            {
                latitude = std::stod(latitudeStr);
                longitude = std::stod(longitudeStr);
            }
            catch (...)
            {
                return CONVERT_ERROR; // Failed to convert latitude/longitude to double
            }
            Sensor sensor(sensorId, latitude, longitude);
            sensorList.push_back(sensor);
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

    std::ifstream file("5_projet_dataset/measurements.csv");
    if (!file.is_open())
    {
        return FILE_ERROR; // Failed to open file
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string timestampStr, sensorId, attributeId, valueStr;
        if (std::getline(ss, timestampStr, ';') && std::getline(ss, sensorId, ';') && std::getline(ss, attributeId, ';') && std::getline(ss, valueStr))
        {
            double value;
            time_t timestamp = parseDateTime(timestampStr.c_str(), "%Y-%m-%d %H:%M:%S");
            if (timestamp == -1)
            {
                return CONVERT_ERROR; // Failed to convert timestamp
            }
            try
            {
                value = std::stod(valueStr);
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

            Measurement measurement(measurementId, attributeId, value);
            measurements[sensorId].push_back(measurement);
        }
        else
        {
            return PARSE_ERROR; // Failed to parse line
        }
    }
}

int DataLoader::loadProviders(list<Provider> &providerList)
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

    std::ifstream file("5_projet_dataset/providers.csv");
    if (!file.is_open())
    {
        return FILE_ERROR; // Failed to open file
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string providerId, cleanerId;
        if (std::getline(ss, providerId, ';') && std::getline(ss, cleanerId))
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
        providerList.push_back(provider);
    }

    return NO_ERROR;
}

int DataLoader::loadUsers(list<User> &userList)
{
    // Implementation for loading users from CSV file
    // Open the CSV file, read each line, parse the data, and populate the userList
    // Return 0 on success, non-zero on failure

    unordered_map<string, list<string>> usersSensors;

    std::ifstream file("5_projet_dataset/users.csv");
    if (!file.is_open())
    {
        return FILE_ERROR; // Failed to open file
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string userId, sensorId;
        if (std::getline(ss, userId, ';') && std::getline(ss, sensorId))
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

        User user(userId);
        for (const string &sensorId : sensorIds)
        {
            user.addSensor(sensorId);
        }
        userList.push_back(user);
    }

    return NO_ERROR;
}

// Private methods

int DataLoader::loadAttributes(unordered_map<string, Attribute> &attributes)
{
    // Implementation for loading attributes from CSV file
    // Open the CSV file, read each line, parse the data, and populate the attributeList
    // Return 0 on success, non-zero on failure

    std::ifstream file("5_projet_dataset/attributes.csv");
    if (!file.is_open())
    {
        return 1; // Failed to open file
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string attributeId, unit, description;
        if (std::getline(ss, attributeId, ';') && std::getline(ss, unit, ';') && std::getline(ss, description))
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

    std::ifstream file("5_projet_dataset/cleaners.csv");
    if (!file.is_open())
    {
        return FILE_ERROR; // Failed to open file
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string cleanerId, latitudeStr, longitudeStr, startTimeStr, stopTimeStr;
        if (std::getline(ss, cleanerId, ';') && std::getline(ss, latitudeStr, ';') && std::getline(ss, longitudeStr, ';') && std::getline(ss, startTimeStr, ';') && std::getline(ss, stopTimeStr))
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
                latitude = std::stod(latitudeStr);
                longitude = std::stod(longitudeStr);
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