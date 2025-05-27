#include <gtest/gtest.h>
#include "../model/User.h"

TEST(TestUser, ConnexionOK)
{
    User u1("toto", "password123");

    EXPECT_TRUE(u1.connecter("password123"));
}

TEST(TestUser, ConnexionKO)
{
    User u1("toto", "password123");

    EXPECT_FALSE(u1.connecter("password12"));
}

TEST(TestUser, ConstructeurCopie)
{
    User u1("toto", "password123");

    User u2 = u1;

    EXPECT_TRUE(u2.connecter("password123"));
}
