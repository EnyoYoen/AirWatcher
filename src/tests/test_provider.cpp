#include <gtest/gtest.h>
#include "../model/Provider.h"

TEST(GettersProvider, ProviderId) {
    std::string s = "test1";
    Provider p(s);

    EXPECT_EQ(p.getProviderId(), s);
}

TEST(SommeTest, CasNegatifs) {
    EXPECT_EQ(-2 + -3, -5);
}

// Point d'entrée des tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
