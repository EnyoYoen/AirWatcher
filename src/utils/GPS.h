/*************************************************************************
                           GPS  -  description
                             -------------------
    début                : 16/5/2025
    copyright            : (C) 2025 par Garoux, Hequet, McCurdy, Lafon de la Laurencie, Peyrot.
*************************************************************************/

#if !defined(GPS_H)
#define GPS_H

#include <cmath>

#define M_PI 3.14159265358979323846

double toRadians ( double degree );
double toDegrees ( double radian );
double distance ( double lat1, double lon1, double lat2, double lon2 );

#endif // GPS_H