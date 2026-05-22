#include <gtest/gtest.h>
#include "../lazy_sequence/Cardinal.hpp"

TEST(cardinal_constructor, basic_constructor_test) {
    Cardinal cardinal;
    ASSERT_EQ(cardinal.is_finite(), 1);
    ASSERT_EQ(cardinal.is_infinite(), 0);
    ASSERT_EQ(cardinal.try_get_size().get_value(), 0);
}

TEST(cardinal_constructor, size_constructor_test) {
    Cardinal cardinal(1);
    EXPECT_EQ(cardinal.is_finite(), 1);
    EXPECT_EQ(cardinal.is_infinite(), 0);
    EXPECT_EQ(cardinal.try_get_size().get_value(), 1);
}

TEST(cardinal_omega, omega_test) {
    Cardinal omega = Cardinal::omega();
    EXPECT_EQ(omega.is_finite(), 0);
    EXPECT_EQ(omega.is_infinite(), 1);
    EXPECT_THROW(omega.try_get_size().get_value(), EmptyOptionException);
}



TEST(cardinal_equal, not_equal_finite_test) {
    Cardinal cardinal_1(5);
    Cardinal cardinal_2(25);
    EXPECT_EQ(cardinal_1 == cardinal_2, 0);
}

TEST(cardinal_equal, equal_finite_test) {
    Cardinal cardinal_1(5);
    Cardinal cardinal_2(5);
    EXPECT_EQ(cardinal_1, cardinal_2);
}

TEST(cardinal_equal, equal_infinite_test) {
    Cardinal omega_1 = Cardinal::omega();
    Cardinal omega_2 = Cardinal::omega();
    EXPECT_EQ(omega_1, omega_2);
}

TEST(cardinal_equal, not_equal_finite_and_infinite_test) {
    Cardinal omega = Cardinal::omega();
    Cardinal cardinal(99999);
    EXPECT_EQ(omega == cardinal, 0);
}



TEST(cardinal_comparision, finite_less_test) {
    Cardinal little(10);
    Cardinal big(100);
    EXPECT_EQ(little < big, 1);
}

TEST(cardinal_comparision, finite_less_equal_test) {
    Cardinal little(10);
    Cardinal big(10);
    EXPECT_EQ(little <= big, 1);
}

TEST(cardinal_comparision, infinite_less_test_1) {
    Cardinal cardinal(10000);
    Cardinal omega = Cardinal::omega();
    EXPECT_EQ(cardinal < omega, 1);
}

TEST(cardinal_comparision, infinite_less_test_2) {
    Cardinal cardinal(10000);
    Cardinal omega = Cardinal::omega();
    EXPECT_EQ(omega < cardinal, 0);
}

TEST(cardinal_comparision, infinite_less_equal_test) {
    Cardinal omega_1 = Cardinal::omega();
    Cardinal omega_2 = Cardinal::omega();
    EXPECT_EQ(omega_2 < omega_1, 0);
}



TEST(cardinal_operations, add_finite_test) {
    Cardinal cardinal_1(10);
    Cardinal cardinal_2(20);
    Cardinal result = cardinal_1 + cardinal_2;

    ASSERT_EQ(result.is_finite(), 1);
    EXPECT_EQ(result.try_get_size().get_value(), 30);
}

TEST(cardinal_operations, finite_add_infinite_test) {
    Cardinal cardinal(10);
    Cardinal omega = Cardinal::omega();
    Cardinal result_1 = cardinal + omega;
    Cardinal result_2 = cardinal + omega;

    ASSERT_EQ(result_1.is_infinite(), 1);
    ASSERT_EQ(result_2.is_infinite(), 1);
    EXPECT_EQ(result_1, Cardinal::omega());
    EXPECT_EQ(result_2, Cardinal::omega());
}

TEST(cardinal_operations, infinite_add_infinite_test) {
    Cardinal omega_1 = Cardinal::omega();
    Cardinal omega_2 = Cardinal::omega();

    Cardinal result = omega_1 + omega_2;

    ASSERT_EQ(result.is_infinite(), 1);
    EXPECT_EQ(result, Cardinal::omega());
}


