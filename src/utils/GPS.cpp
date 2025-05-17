#include "GPS.h"

double toRadians ( double degree )
{
    return degree * M_PI / 180.0;
}

double toDegrees ( double radian )
{
    return radian * 180.0 / M_PI;
}

double distance ( double lat1, double lon1, double lat2, double lon2 )
{
    // Haversine formula to calculate the distance between two points on the Earth
    const double R = 6371.0;
    double dLat = toRadians(lat2 - lat1);
    double dLon = toRadians(lon2 - lon1);
    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(toRadians(lat1)) * cos(toRadians(lat2)) *
               sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return R * c;
}