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
}