#include <gtest/gtest.h>
#include "../model/Sensor.h"

TEST(TestSensor, CheckDistanceSamePoint) {
    Sensor s("id1", 1.4, 4.1);

    EXPECT_TRUE(s.checkDistance(1.4, 4.1, 0));
}

TEST(TryFalse, failed) {
    EXPECT_TRUE(false);
}