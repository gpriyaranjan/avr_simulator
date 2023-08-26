#include "gtest/gtest.h"
#include "decoder.h"
#include "environment.h"

TEST(FlagsTest, AddSmall1) {
    UChar source = 20;
    UChar target = 17;
    UChar result = 37;
    SReg sReg;
    statusFlags(source, target, result, sReg);
    EXPECT_EQ(sReg.N, false);
    EXPECT_EQ(sReg.Z, false);
    EXPECT_EQ(sReg.S, false);
    EXPECT_EQ(sReg.C, false);
    EXPECT_EQ(sReg.V, false);
}

TEST(FlagsTest, AddSmall2) {
    UChar source = 20;
    UChar target = -17;
    UChar result = -3;
    SReg sReg;
    statusFlags(source, target, result, sReg);
    EXPECT_EQ(sReg.N, true);
    EXPECT_EQ(sReg.Z, false);
    EXPECT_EQ(sReg.S, false);
    EXPECT_EQ(sReg.C, false);
    EXPECT_EQ(sReg.V, false);
}

TEST(FlagsTest, AddSmall3) {
    UChar source = -17;
    UChar target = 20;
    UChar result =  3;
    SReg sReg;
    statusFlags(source, target, result, sReg);
    EXPECT_EQ(sReg.N, false);
    EXPECT_EQ(sReg.Z, false);
    EXPECT_EQ(sReg.S, false);
    EXPECT_EQ(sReg.C, true);
    EXPECT_EQ(sReg.V, false);
}

TEST(FlagsTest, AddSmall4) {
    UChar source = 20;
    UChar target = -27;
    UChar result = -7;
    SReg sReg;
    statusFlags(source, target, result, sReg);
    EXPECT_EQ(sReg.N, true);
    EXPECT_EQ(sReg.Z, false);
    EXPECT_EQ(sReg.S, false);
    EXPECT_EQ(sReg.C, false);
    EXPECT_EQ(sReg.V, false);
}

TEST(FlagsTest, Overflow1) {
    UChar source = 0x20;
    UChar target = 0x65;
    UChar result = 0x85;

    SReg sReg;
    statusFlags(source, target, result, sReg);

    EXPECT_EQ(sReg.N, true);
    EXPECT_EQ(sReg.Z, false);
    EXPECT_EQ(sReg.S, true);
    EXPECT_EQ(sReg.C, false);
    EXPECT_EQ(sReg.V, true);
}