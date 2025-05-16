/*************************************************************************
                           DateTime  -  description
                             -------------------
    début                : 16/5/2025
    copyright            : (C) 2025 par Garoux, Hequet, McCurdy, Lafon de la Laurencie, Peyrot.
*************************************************************************/

#ifndef DATETIME_H
#define DATETIME_H

#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

time_t parseDateTime(const char* datetimeString, const char* format) {
    struct tm tmStruct = {};
    istringstream ss(datetimeString);
    ss >> get_time(&tmStruct, format);
    
    if (ss.fail()) {
        return -1; // parsing failed
    }

    return mktime(&tmStruct); // returns time_t in local time
}

#endif // DATETIME_H