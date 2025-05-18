#include "DateTime.h"

time_t parseDateTime(const char* datetimeString, const char* format) {
    struct tm tmStruct = {};
    istringstream ss(datetimeString);
    ss >> get_time(&tmStruct, format);
    
    if (ss.fail()) {
        return -1; // parsing failed
    }

    return mktime(&tmStruct); // returns time_t in local time
}