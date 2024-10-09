
#include <iostream>
#include <gtest/gtest.h>
#include "bitArray.h"


TEST(BitArrayTest, DefaultConstructor){
  BitArray a1;
  ASSERT_EQ(a1.size(), 0);
  ASSERT_TRUE(a1.empty());
}

TEST(BitArrayTest, ConstructorWithInvalidSize){
  ASSERT_THROW(BitArray a1(-1), std::invalid_argument);
}

TEST(BitArrayTest, ConstructorWithSizeWithoutValue){
  BitArray a1(70);
  ASSERT_EQ(a1.size(), 70);
  ASSERT_TRUE(a1.none());
}

TEST(BitArrayTest, ConstructorWithSizeAndValue){
  BitArray a1(8, 3UL);
  ASSERT_EQ(a1.size(), 8);
  ASSERT_FALSE(a1.empty());
  ASSERT_EQ(a1.count(), 2);
  ASSERT_EQ(a1.size(), std::min(a1.size(), 64));
  ASSERT_EQ(a1.toString(), "00000011");
}

TEST(BitArrayTest, ConstructorCopy){
  BitArray a1(8, 3);
  BitArray a2(a1);
  ASSERT_EQ(a2.size(), 8);
  ASSERT_FALSE(a2.empty());
  ASSERT_EQ(a2.count(), 2);
  ASSERT_EQ(a2.toString(), "00000011");
}

TEST(BitArrayTest, Swap){
  BitArray a1(8, 3);
  BitArray a2(10, 5);
  a1.swap(a2);
  ASSERT_EQ(a1.toString(), "0000000101");
  ASSERT_EQ(a2.toString(), "00000011");
}

TEST(BitArrayTest, Assigment){
  BitArray a1(8, 2);
  BitArray a2 = a1;
  ASSERT_EQ(a1.size(), a2.size());
  ASSERT_EQ(a1.toString(), a2.toString());    
}

TEST(BitArrayTest, AssigmentEQ){
  BitArray a1(8,2);
  BitArray a2(8,2);
  a2 = a1;
  ASSERT_EQ(a1.size(), a2.size());
  ASSERT_EQ(a1.toString(), a2.toString());    
}

TEST(BitArrayTest,CheckResizeNull){
  BitArray a1(8, 2);
  a1.resize(0);
  ASSERT_EQ(a1.size(), 0);
  ASSERT_EQ(a1.toString(),"");
}

TEST(BitArrayTest, CheckResizeWithoutValue){
  BitArray a1(8,3);
  a1.resize(4);
  ASSERT_EQ(a1.toString(),  "0011");
  ASSERT_EQ(a1.size(), 4);
  a1.resize(8);
  ASSERT_EQ(a1.toString(), "00110000");
  ASSERT_EQ(a1.size(), 8);
}
 
TEST(BitArrayTest, CheckResizeWithValue){
  BitArray a1(8,3);
  a1.resize(4, true);
  ASSERT_EQ(a1.toString(),  "0011");
  ASSERT_EQ(a1.size(), 4);
  a1.resize(8, true);
  ASSERT_EQ(a1.toString(), "00111111");
  ASSERT_EQ(a1.size(), 8);
}
TEST(BitArrayTest, CheckResizeWithInvalidSize){
  BitArray a1(8, 3);
  ASSERT_THROW(a1.resize(-1), std::invalid_argument);
}

TEST(BitArrayTest, CheckClear){
  BitArray a1(8, 3);
  a1.clear();
  ASSERT_EQ(a1.size(), 0);
  ASSERT_EQ(a1.toString(), "");
}

TEST(BitArrayTest, CheckPushBack){
  BitArray a1(8, 3);
  a1.pushBack(true);
  a1.pushBack(false);
  ASSERT_EQ(a1.size(), 10);
  ASSERT_EQ(a1.toString(), "0000001110");
}

TEST(BitArrayTest, CheckANDAssignInvalidArgument) {
  BitArray a1(2, 1);
  BitArray a2(4, 3);
  ASSERT_THROW(a1 &= a2, std::invalid_argument);
}

TEST(BitArrayTest, CheckANDAssign) {
  BitArray a1(4, 1);
  BitArray a2(4, 3);
  a1 &= a2;
  ASSERT_EQ(a1.toString(), "0001");
}

TEST(BitArrayTest, CheckORAssignInvalidArgument) {
  BitArray a1(2, 1);
  BitArray a2(4, 3);
  ASSERT_THROW(a1 |= a2, std::invalid_argument);
}

TEST(BitArrayTest, CheckORAssign) {
  BitArray a1(4, 1);
  BitArray a2(4, 3);
  a1 |= a2;
  ASSERT_EQ(a1.toString(), "0011");
}
TEST(BitArrayTest, CheckXORAssignInvalidArgument) {
  BitArray a1(2, 1);
  BitArray a2(4, 3);
  ASSERT_THROW(a1 ^= a2, std::invalid_argument);
}

TEST(BitArrayTest, CheckXORAssign) {
  BitArray a1(4, 1);
  BitArray a2(4, 3);
  a1 ^= a2;
  ASSERT_EQ(a1.toString(), "0010");
}



TEST(BitArrayTest, CheckLeftShiftAndAssignWithIvalidIndex){
  BitArray a1(8, 3);
  ASSERT_THROW(a1 <<= -1, std::invalid_argument);
}

TEST(BitArrayTest, CheckLeftShiftAndAssign){
  BitArray a1(8, 3);
  ASSERT_EQ(a1.toString(), "00000011");
  a1 <<= 3;
  ASSERT_EQ(a1.toString(), "00011000");
  a1 <<= 100; 
  ASSERT_EQ(a1.toString(), "00000000");
}


TEST(BitArrayTest, CheckRightShiftAndAssignWithIvalidIndex){
  BitArray a1(8, 3);
  ASSERT_THROW(a1 >>= -1, std::invalid_argument);
}

TEST(BitArrayTest, CheckRightShiftAndAssign){
  BitArray a1(8, 15);
  ASSERT_EQ(a1.toString(), "00001111");
  a1 >>= 2;
  ASSERT_EQ(a1.toString(), "00000011");
  a1 >>= 100; 
  ASSERT_EQ(a1.toString(), "00000000");
}

TEST(BitArrayTest, CheckLeftShiftWithInvalidIndex){
  BitArray a1(8, 3);
  ASSERT_THROW(a1 << -1, std::invalid_argument);
}

TEST(BitArrayTest, CheckLeftShift){
  BitArray a1(8, 3);
  ASSERT_EQ((a1 << 1).toString(), "00000110");
  ASSERT_EQ((a1 << 100).toString(), "00000000");
}

TEST(BitArrayTest, CheckRighttShiftWithInvalidIndex){
  BitArray a1(8, 3);
  ASSERT_THROW(a1 >> -1, std::invalid_argument);
}

TEST(BitArrayTest, CheckRightShift){
  BitArray a1(8, 3);
  ASSERT_EQ((a1 >> 1).toString(), "00000001");
  ASSERT_EQ((a1 >> 100).toString(), "00000000");
}



TEST(BitArrayTest, CheckSetOneWithInvalidIndex){
  BitArray a1(8);
  ASSERT_THROW(a1.set(-1), std::invalid_argument);
  ASSERT_THROW(a1.set(9), std::invalid_argument);
}

TEST(BitArrayTest, CheckSetOne){
  BitArray a1(8);
  a1.set(1);
  a1.set(2, false);
  a1.set(3, true);
  ASSERT_EQ(a1.toString(), "01010000");
}

TEST(BitArrayTest, CheckSetAll){
  BitArray a1(8);
  a1.set();
  ASSERT_EQ(a1.count(), 8);
  ASSERT_EQ(a1.toString(), "11111111");
}

TEST(BitArrayTest, CheckResetOneWithInvalidIndex){
  BitArray a1(8);
  ASSERT_THROW(a1.reset(-1), std::invalid_argument);
  ASSERT_THROW(a1.reset(9), std::invalid_argument);
}

TEST(BitArrayTest, CheckResetOne){
  BitArray a1(8);
  a1.set();
  a1.reset(1);
  a1.reset(3);
  ASSERT_EQ(a1.toString(), "10101111");
}

TEST(BitArrayTest, CheckResetAll){
  BitArray a1(8);
  a1.reset();
  ASSERT_EQ(a1.count(), 0);
  ASSERT_EQ(a1.toString(), "00000000");
}

TEST(BitArrayTest, CheckAny){
  BitArray a1(70);
  ASSERT_FALSE(a1.any());
  
  BitArray a2(70);
  a2.set(1);
  ASSERT_TRUE(a2.any());

  BitArray a3(70);
  a3.set(67);
  ASSERT_TRUE(a3.any());
}

TEST(BitArrayTest, CheckNone){
  BitArray a1(70);
  ASSERT_TRUE(a1.none());
  
  BitArray a2(70);
  a2.set(1);
  ASSERT_FALSE(a2.none());

  BitArray a3(70);
  a3.set(67);
  ASSERT_FALSE(a3.none());
}

TEST(BitArrayTest, CheckInvert){
  BitArray a1(8, 3);
  ASSERT_EQ((~a1).toString(), "11111100");
}

TEST(BitArrayTest, CheckCount){
  BitArray a1(8, 3);
  ASSERT_EQ(a1.count(), 2);
  a1.resize(20);
  a1.set();
  ASSERT_EQ(a1.count(), 20);
}

TEST(BitArrayTest, CheckIndex){
  BitArray a1(5, 3);
  ASSERT_EQ(a1[0],  false);
  ASSERT_EQ(a1[1],  false);
  ASSERT_EQ(a1[2],  false);
  ASSERT_EQ(a1[3],  true);
  ASSERT_EQ(a1[4],  true);
}

TEST(BitArrayTest, CheckSize){
  BitArray a1(8);
  BitArray a2(90);
  ASSERT_EQ(a1.size(),  8);
  ASSERT_EQ(a2.size(),  90);
}

TEST(BitArrayTest, CheckEmpty){
  BitArray a1(8);
  BitArray a2;
  ASSERT_EQ(a1.empty(),  false);
  ASSERT_EQ(a2.empty(),  true);
}

TEST(BitArrayTest, CheckToString){
  BitArray a1(8, 3);
  ASSERT_EQ(a1.toString(), "00000011");
}

TEST(BitArrayTest, CheckEqually){
  BitArray a1(8, 3);
  BitArray a2(8, 3);
  BitArray a3(18, 3);
  ASSERT_TRUE(a1 == a2);
  ASSERT_FALSE(a1 == a3);
}

TEST(BitArrayTest, CheckNotEqually){
  BitArray a1(8, 3);
  BitArray a2(8, 3);
  BitArray a3(18, 3);
  ASSERT_TRUE(a1 != a3);
  ASSERT_FALSE(a1 != a2);
}

TEST(BitArrayTest, CheckANDWithDiffSizes){
  BitArray a1(8, 3);
  BitArray a2(18, 3);
  ASSERT_THROW(a1 & a2, std::invalid_argument);
}

TEST(BitArrayTest, CheckAND){
  BitArray a1(8, 5);
  BitArray a2(8, 3);
  ASSERT_EQ((a1 & a2).toString(), "00000001");
}

TEST(BitArrayTest, CheckORWithDiffSizes){
  BitArray a1(8, 3);
  BitArray a2(18, 3);
  ASSERT_THROW(a1 | a2, std::invalid_argument);
}

TEST(BitArrayTest, CheckOR){
  BitArray a1(8, 5);
  BitArray a2(8, 3);
  ASSERT_EQ((a1 | a2).toString(), "00000111");
}
TEST(BitArrayTest, CheckXORWithDiffSizes){
  BitArray a1(8, 3);
  BitArray a2(18, 3);
  ASSERT_THROW(a1 ^ a2, std::invalid_argument);
}

TEST(BitArrayTest, CheckXOR){
  BitArray a1(8, 5);
  BitArray a2(8, 3);
  ASSERT_EQ((a1 ^ a2).toString(), "00000110");
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
