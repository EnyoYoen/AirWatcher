/*************************************************************************
                           DateTime  -  description
                             -------------------
    début                : 16/5/2025
    copyright            : (C) 2025 par Garoux, Hequet, McCurdy, Lafon de la Laurencie, Peyrot.
*************************************************************************/

#if !defined(DATETIME_H)
#define DATETIME_H

#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

time_t parseDateTime(const char* datetimeString, const char* format);

#endif // DATETIME_H