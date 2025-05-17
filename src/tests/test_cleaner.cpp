#include <gtest/gtest.h>
#include "../model/Provider.h"

TEST(GettersCleaner, getCleanerId) {
    std::string s = "test1";
    time_t t;
    Cleaner c(s, 0.0, 1.0, t, t);

    EXPECT_EQ(c.getCleanerId(), s);
}

