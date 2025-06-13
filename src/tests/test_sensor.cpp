#include <gtest/gtest.h>
#include "../model/Sensor.h"

TEST(TestSensor, CheckDistanceSamePoint) {
    Sensor s("id1", 1.4, 4.1);

    EXPECT_TRUE(s.checkDistance(1.4, 4.1, 0));
}

TEST(TestSensor, CheckDistanceZeroRadius) {
    Sensor s("id1", 10.4, 40.1);

    EXPECT_FALSE(s.checkDistance(1.4, 4.1, 0));
}

TEST(TestSensor, CheckDistanceNegativeRadius) {
    Sensor s("id1", 1.4, 4.1);

    EXPECT_FALSE(s.checkDistance(1.4, 2.1, -1));
}

TEST(SensorTest, DistancePlusRadius) {
    Sensor sensor("Paris", 48.8566, 2.3522); 
    double lat = 48.8566 + (10.0 / 111.0); // Approx 10 km north
    EXPECT_TRUE(sensor.checkDistance(lat, 2.3522, 11.0));
}

TEST(SensorTest, CalculateAirQuality_SinglePM10Measurement) {
    Sensor sensor;
    time_t now = time(nullptr);
    vector<Measurement> data = {
        Measurement(now, "PM10", 35.0f)
    };

    float result = sensor.calculateAirQuality(now - 10, now + 10, data);

    EXPECT_FLOAT_EQ(result, 50.0f);
}

TEST(SensorTest, CalculateAirQuality_MultipleMeasurements) {
    Sensor sensor;
    time_t now = time(nullptr);
    vector<Measurement> data = {
        Measurement(now, "PM10", 17.5f),  // 25
        Measurement(now, "NO2", 213.0f),  // 50
        Measurement(now, "O3", 41.0f),    // 25
        Measurement(now, "SO2", 100.0f)   // 25
    };

    float result = sensor.calculateAirQuality(now - 10, now + 10, data);
    EXPECT_FLOAT_EQ(result, 50.0f);  // max of the four = 50
}

TEST(SensorTest, CalculateAirQuality_OutsideTimeRange) {
    Sensor sensor;
    time_t now = time(nullptr);
    vector<Measurement> data = {
        Measurement(now - 1000, "PM10", 100.0f),
        Measurement(now + 1000, "NO2", 200.0f)
    };

    float result = sensor.calculateAirQuality(now - 10, now + 10, data);
    EXPECT_FLOAT_EQ(result, 0.0f);  // no measurements in range
}

TEST(SensorTest, CalculateAirQuality_EmptyMeasurementList) {
    Sensor sensor;
    time_t now = time(nullptr);
    vector<Measurement> data;

    float result = sensor.calculateAirQuality(now - 10, now + 10, data);
    EXPECT_FLOAT_EQ(result, 0.0f);  // no data at all
}

TEST(SensorTest, CalculateAirQuality_MixedValidAndInvalidAttributes) {
    Sensor sensor;
    time_t now = time(nullptr);
    vector<Measurement> data = {
        Measurement(now, "PM10", 35.0f),
        Measurement(now, "XYZ", 100.0f),  // ignored
        Measurement(now, "O3", 82.0f)
    };

    float result = sensor.calculateAirQuality(now - 10, now + 10, data);
    // PM10 = 50, O3 = 50 → max = 50
    EXPECT_FLOAT_EQ(result, 50.0f);
}