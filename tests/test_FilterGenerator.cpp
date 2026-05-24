#include <gtest/gtest.h>
#include "../generators/FilterGenerator.hpp"
#include "../generators/ContainerGenerator.hpp"
#include "../generators/RecurrentGenerator.hpp"
#include "../libs/Lab_3/exceptions/Option.hpp"
#include "../libs/Lab_3/array_sequence/MutableArraySequence.hpp"

TEST(filter_generator, even_test) {

    auto predicate = [](int x) -> bool {
        return x % 2 == 0;
    };

    int array[] = {10, 15, 20, 25, 30, 35};
    MutableArraySequence<int> sequence(array, 6);
    auto container = std::make_shared<ContainerGenerator<int, MutableArraySequence>>(sequence);
    auto filter_generator = std::make_shared<FilterGenerator<int>>(container, predicate);

    EXPECT_EQ(filter_generator->size().get_size(), 3);
    EXPECT_EQ(filter_generator->get_next(), 10);
    EXPECT_EQ(filter_generator->get_next(), 20);
    EXPECT_EQ(filter_generator->get_next(), 30);
}

TEST(filter_generator, fibonacci_even_test) {
    auto fibonacci = [](const MutableArraySequence<int>& sequence) -> int {
        size_t n = sequence.get_length();
        if (n < 2) {
            return 1;
        }
        return sequence[n - 1] + sequence[n - 2];
    };

    auto predicate = [](int x) -> bool {
        return x % 2 == 0;
    };

    MutableArraySequence<int> cache;
    auto container = std::make_shared<RecurrentGenerator<int, MutableArraySequence>>(fibonacci, cache);
    auto filter_generator = std::make_shared<FilterGenerator<int>>(container, predicate);

    EXPECT_EQ(filter_generator->size().is_infinite(), 1);
    EXPECT_EQ(filter_generator->get_next(), 2);
    EXPECT_EQ(filter_generator->get_next(), 8);
    EXPECT_EQ(filter_generator->get_next(), 34);
    EXPECT_EQ(filter_generator->get_next(), 144);
}