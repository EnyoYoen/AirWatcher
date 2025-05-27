#include <gtest/gtest.h>
#include "../model/User.h"

TEST(TestUser, getUserId)
{
    User u1("toto");

    EXPECT_EQ(u1.getUserId(), "toto");
}

TEST(TestUser, ConstructeurCopie)
{
    User u1("toto");

    User u2 = u1;

    EXPECT_EQ(u2.getUserId(), "toto");
}
