#include <gtest/gtest.h>
#include "../model/User.h"

TEST(TestUser, ConnexionOK) {
    User u1(1, "password123");

    EXPECT_TRUE(u1.Connecter("password123"));
}

TEST(TestUser, ConnexionKO) {
    User u1(1, "password123");

    EXPECT_FALSE(u1.Connecter("password12"));
}

TEST(TestUser, ConstructeurCopie) {
    User u1(1, "password123");

    User u2 = u1; 

    EXPECT_TRUE(u2.Connecter("password123"));
}


/*
User u1(1, "password123");
    User u2 = u1;
    cout<< "Test User"<<endl;
    cout <<"\tTrue: " << u1.Connecter("password123") << " False: "<< u1.Connecter("password12") << endl;


    //PRIVATE_USER
    PrivateUser p1(2, "password123");
    cout<< "Test PrivateUser" <<endl;
    cout << "\tReliable:" << p1.isReliable()<< endl;
    cout << "\tPoints:" << p1.getPoints()<< endl;
    p1.setReliable(false);
    p1.givePoints(5);
    p1.givePoints(-10);
    cout<<"\tModif"<<endl;
    cout << "\tReliable:" << p1.isReliable()<< endl;
    cout << "\tPoints:" << p1.getPoints()<< endl;*/