#include <gtest/gtest.h>
#include "../model/PrivateUser.h"

TEST(TestPrivateUser, ConnexionOK) {
    PrivateUser p1(2, "password123");

    EXPECT_TRUE(p1.Connecter("password123"));
}

TEST(TestPrivateUser, ConnexionKO) {
    PrivateUser p1(2, "password123");

    EXPECT_FALSE(p1.Connecter("password12"));
}

TEST(TestPrivateUser, ConstructeurCopie) {
    PrivateUser p1(2, "password123");

    PrivateUser p2 = p1; 

    EXPECT_TRUE(p2.Connecter("password123"));
}

TEST(TestPrivateUser, Reliable) {
    PrivateUser p1(2, "password123");

    EXPECT_TRUE(p1.isReliable());

    p1.setReliable(false);

    EXPECT_FALSE(p1.isReliable());

    p1.setReliable(true);

    EXPECT_TRUE(p1.isReliable());
}

TEST(TestPrivateUser, Points) {
    PrivateUser p1(2, "password123");

    EXPECT_EQ(p1.getPoints(), 0);

    p1.givePoints(2);

    EXPECT_EQ(p1.getPoints(), 2);

    p1.givePoints(-12);

    EXPECT_EQ(p1.getPoints(), -10);
}
