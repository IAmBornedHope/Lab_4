#include <gtest/gtest.h>
#include "../lazy_sequence/Cardinal.hpp"

TEST(cardinal_constructor, basic_constructor_test) {
    Cardinal cardinal(0);
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

TEST(cardinal_aleph_null, aleph_null_test) {
    Cardinal aleph_null = Cardinal::aleph_null();
    EXPECT_EQ(aleph_null.is_finite(), 0);
    EXPECT_EQ(aleph_null.is_infinite(), 1);
    EXPECT_THROW(aleph_null.try_get_size().get_value(), EmptyOptionException);
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
    Cardinal aleph_null_1 = Cardinal::aleph_null();
    Cardinal aleph_null_2 = Cardinal::aleph_null();
    EXPECT_EQ(aleph_null_1, aleph_null_2);
}

TEST(cardinal_equal, not_equal_finite_and_infinite_test) {
    Cardinal aleph_null = Cardinal::aleph_null();
    Cardinal cardinal(99999);
    EXPECT_EQ(aleph_null == cardinal, 0);
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
    Cardinal aleph_null = Cardinal::aleph_null();
    EXPECT_EQ(cardinal < aleph_null, 1);
}

TEST(cardinal_comparision, infinite_less_test_2) {
    Cardinal cardinal(10000);
    Cardinal aleph_null = Cardinal::aleph_null();
    EXPECT_EQ(aleph_null < cardinal, 0);
}

TEST(cardinal_comparision, infinite_less_equal_test) {
    Cardinal aleph_null_1 = Cardinal::aleph_null();
    Cardinal aleph_null_2 = Cardinal::aleph_null();
    EXPECT_EQ(aleph_null_2 < aleph_null_1, 0);
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
    Cardinal aleph_null = Cardinal::aleph_null();
    Cardinal result_1 = cardinal + aleph_null;
    Cardinal result_2 = cardinal + aleph_null;

    ASSERT_EQ(result_1.is_infinite(), 1);
    ASSERT_EQ(result_2.is_infinite(), 1);
    EXPECT_EQ(result_1, Cardinal::aleph_null());
    EXPECT_EQ(result_2, Cardinal::aleph_null());
}

TEST(cardinal_operations, infinite_add_infinite_test) {
    Cardinal aleph_null_1 = Cardinal::aleph_null();
    Cardinal aleph_null_2 = Cardinal::aleph_null();

    Cardinal result = aleph_null_1 + aleph_null_2;

    ASSERT_EQ(result.is_infinite(), 1);
    EXPECT_EQ(result, Cardinal::aleph_null());
}


