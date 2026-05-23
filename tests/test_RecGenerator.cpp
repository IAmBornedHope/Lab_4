#include <gtest/gtest.h>
#include "../generators/RecurrentGenerator.hpp"
#include "../libs/Lab_3/exceptions/Option.hpp"
#include "../libs/Lab_3/array_sequence/MutableArraySequence.hpp"

TEST(recurrent_generator, basic_const_test) {
    auto function = [](const MutableArraySequence<double>& sequence) {
        return 10.10;
    };
    
    MutableArraySequence<double> cache;
    RecurrentGenerator<double, MutableArraySequence> generator(function, cache);

    ASSERT_EQ(generator.size().is_infinite(), 1);
    EXPECT_EQ(generator.has_next(), 1);
    EXPECT_EQ(generator.get_position(), 0);
    EXPECT_EQ(generator.get_next(), 10.10);
    EXPECT_EQ(generator.get_position(), 1);
}

TEST(recurrent_generator, fibonacci_test) {
    auto function = [](const MutableArraySequence<int>& sequence) -> int {
        size_t n = sequence.get_length();
        if (n < 2) {
            return 1;
        }
        return sequence[n - 1] + sequence[n - 2];
    };
    
    MutableArraySequence<int> cache;
    RecurrentGenerator<int, MutableArraySequence> generator(function, cache);

    EXPECT_EQ(generator.get_next(), 1);
    EXPECT_EQ(generator.get_next(), 1);
    EXPECT_EQ(generator.get_next(), 2);
    EXPECT_EQ(generator.get_next(), 3);
    EXPECT_EQ(generator.get_next(), 5);
    EXPECT_EQ(generator.get_next(), 8);

}