#include "gtest/gtest.h"
#include "environment.h"

Environment environment;

TEST(InitTest, StatusSet) {
    environment.sReg.Z = true;
    EXPECT_EQ(*((char *) &environment.sReg), 2);
}

TEST(InitTest, EnvInit) {
    environment.sReg.Z = true;
    EXPECT_EQ(*((char *) &environment.sReg), 2);

    environment.init();
    EXPECT_EQ(*((char *)&environment.sReg), 0);
}
