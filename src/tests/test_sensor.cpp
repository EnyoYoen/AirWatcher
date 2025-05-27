#include <gtest/gtest.h>
#include "../model/Sensor.h"

TEST(TestSensor, CheckDistanceSamePoint) {
    Sensor s("id1", 1.4, 4.1);

    EXPECT_TRUE(s.checkDistance(1.4, 4.1, 0));
}

TEST(TestSensor, CheckDistanceNegativeRadius) {
    Sensor s("id1", 1.4, 4.1);

    EXPECT_FALSE(s.checkDistance(1.4, 2.1, -1));
}
