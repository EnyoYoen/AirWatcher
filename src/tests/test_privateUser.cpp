#include <gtest/gtest.h>
#include "../model/PrivateUser.h"

TEST(TestPrivateUser, ConnexionOK)
{
    PrivateUser p1("tata");

    // TODO    EXPECT_TRUE(p1.connecter("password123"));
}

TEST(TestPrivateUser, ConnexionKO)
{
    PrivateUser p1("tata");

    //    EXPECT_FALSE(p1.connecter("password12"));
}

TEST(TestPrivateUser, ConstructeurCopie)
{
    PrivateUser p1("tata");

    PrivateUser p2 = p1;

    //    EXPECT_TRUE(p2.connecter("password123"));
}

TEST(TestPrivateUser, Reliable)
{
    PrivateUser p1("tata");

    EXPECT_TRUE(p1.isReliable());

    p1.setReliable(false);

    EXPECT_FALSE(p1.isReliable());

    p1.setReliable(true);

    EXPECT_TRUE(p1.isReliable());
}

TEST(TestPrivateUser, Points)
{
    PrivateUser p1("tata");

    EXPECT_EQ(p1.getPoints(), 0);

    p1.addPoints();

    EXPECT_EQ(p1.getPoints(), 1);

    p1.addPoints();

    EXPECT_EQ(p1.getPoints(), 2);
}
