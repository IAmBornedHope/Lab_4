#include <gtest/gtest.h>
#include "../generators/MapGenerator.hpp"
#include "../generators/ContainerGenerator.hpp"
#include "../generators/RecurrentGenerator.hpp"
#include "../libs/Lab_3/exceptions/Option.hpp"
#include "../libs/Lab_3/array_sequence/MutableArraySequence.hpp"

TEST(map_generator, multiply_on_two_test) {

    auto function = [](int x) {
        return x * 2;
    };

    int array[] = {10, 20, 30};
    MutableArraySequence<int> sequence(array, 3);
    auto container = std::make_shared<ContainerGenerator<int, MutableArraySequence>>(sequence);
    auto map_generator = std::make_shared<MapGenerator<int, int>>(container, function);

    EXPECT_EQ(map_generator->size(), 3);
    EXPECT_EQ(map_generator->get_next(), 20);
    EXPECT_EQ(map_generator->get_next(), 40);
    EXPECT_EQ(map_generator->get_next(), 60);
}

TEST(map_generator, infinite_multiply_on_two_test) {
    auto fibonacci = [](const MutableArraySequence<int>& sequence) -> int {
        size_t n = sequence.get_length();
        if (n < 2) {
            return 1;
        }
        return sequence[n - 1] + sequence[n - 2];
    };

    auto function = [](int x) {
        return x * 2;
    };

    MutableArraySequence<int> cache;
    auto container = std::make_shared<RecurrentGenerator<int, MutableArraySequence>>(fibonacci, cache);
    auto map_generator = std::make_shared<MapGenerator<int, int>>(container, function);

    EXPECT_EQ(map_generator->size().is_infinite(), 1);
    EXPECT_EQ(map_generator->get_next(), 2);
    EXPECT_EQ(map_generator->get_next(), 2);
    EXPECT_EQ(map_generator->get_next(), 4);
    EXPECT_EQ(map_generator->get_next(), 6);
    EXPECT_EQ(map_generator->get_next(), 10);
    EXPECT_EQ(map_generator->get_next(), 16);
}