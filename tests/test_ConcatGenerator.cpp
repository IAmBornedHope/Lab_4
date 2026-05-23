#include <gtest/gtest.h>
#include "../generators/ConcatGenerator.hpp"
#include "../generators/ContainerGenerator.hpp"
#include "../generators/RecurrentGenerator.hpp"
#include "../libs/Lab_3/exceptions/Option.hpp"
#include "../libs/Lab_3/array_sequence/MutableArraySequence.hpp"

TEST(concat_generator, basic_concat_test) {
    int arr_1[] = {1, 2};
    MutableArraySequence<int> first_sequence(arr_1, 2);
    auto first = std::make_shared<ContainerGenerator<int, MutableArraySequence>>(first_sequence);

    int arr_2[] = {3, 4, 5};
    MutableArraySequence<int> second_sequence(arr_2, 3);
    auto second = std::make_shared<ContainerGenerator<int, MutableArraySequence>>(second_sequence);

    auto concat_generator = std::make_shared<ConcatGenerator<int>>(first, second);

    EXPECT_EQ(concat_generator->size().get_size(), 5);
    EXPECT_EQ(concat_generator->get_next(), 1);
    EXPECT_EQ(concat_generator->get_next(), 2);
    EXPECT_EQ(concat_generator->get_next(), 3);
    EXPECT_EQ(concat_generator->get_next(), 4);
    EXPECT_EQ(concat_generator->get_next(), 5);
    EXPECT_THROW(concat_generator->get_next(), IndexOutOfRangeException);
}

TEST(concat_generator, finite_concat_infinite_test) {
    int arr[] = {1, 2};
    MutableArraySequence<int> sequence(arr, 2);
    auto first = std::make_shared<ContainerGenerator<int, MutableArraySequence>>(sequence);

    auto fibonacci = [](const MutableArraySequence<int>& sequence) -> int {
        size_t n = sequence.get_length();
        if (n < 2) {
            return 1;
        }
        return sequence[n - 1] + sequence[n - 2];
    };

    MutableArraySequence<int> cache;
    auto second = std::make_shared<RecurrentGenerator<int, MutableArraySequence>>(fibonacci, cache);
    auto concat_generator = std::make_shared<ConcatGenerator<int>>(first, second);

    EXPECT_EQ(concat_generator->size().is_infinite(), 1);
    EXPECT_EQ(concat_generator->get_next(), 1);
    EXPECT_EQ(concat_generator->get_next(), 2);
    EXPECT_EQ(concat_generator->get_next(), 1);
    EXPECT_EQ(concat_generator->get_next(), 1);
    EXPECT_EQ(concat_generator->get_next(), 2);
    EXPECT_EQ(concat_generator->get_next(), 3);
    EXPECT_EQ(concat_generator->get_next(), 5);
}