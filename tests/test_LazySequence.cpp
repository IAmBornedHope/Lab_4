#include <gtest/gtest.h>
#include "../lazy_sequence/LazySequence.hpp"
#include "../generators/RecurrentGenerator.hpp"

using LazyInt = LazySequence<int, MutableArraySequence>;
using GenInt = std::shared_ptr<IGenerator<int>>;

TEST(lazy_sequence_constructor, constructor_from_array_test) {
    int array[] = {10, 20, 30};
    auto sequence = std::make_shared<LazyInt>(array, 3);

    ASSERT_EQ(sequence->get_length().get_size(), 3);
    EXPECT_EQ(sequence->get(Cardinal(0)), 10);
    EXPECT_EQ(sequence->get(Cardinal(1)), 20);
    EXPECT_EQ(sequence->get(Cardinal(2)), 30);
}

TEST(lazy_sequence_constructor, constructor_from_container_test) {
    MutableArraySequence<int> cache;
    auto sequence = std::make_shared<LazyInt>(cache);

    ASSERT_EQ(sequence->get_length().get_size(), 0);
    EXPECT_THROW(sequence->get_first(), InvalidArgumentException);
}

TEST(lazy_sequence_constructor, fibonacci_test) {
    auto fibonacci = [](const MutableArraySequence<int>& sequence) -> int {
        return sequence[sequence.get_length() - 1] + sequence[sequence.get_length() - 2];
    };

    MutableArraySequence<int> cache;
    cache.append(1);
    cache.append(1);

    auto generator = std::make_shared<RecurrentGenerator<int, MutableArraySequence>>(fibonacci, cache);
    auto sequence = std::make_shared<LazyInt>(cache, generator);

    ASSERT_EQ(sequence->get_length().is_infinite(), 1);
    EXPECT_EQ(sequence->get_materialized_count(), 2);

    EXPECT_EQ(sequence->get(Cardinal(4)), 5);
    EXPECT_EQ(sequence->get_materialized_count(), 5);

    EXPECT_EQ(sequence->get(Cardinal(4)), 5);
    EXPECT_EQ(sequence->get_materialized_count(), 5);

    EXPECT_THROW(sequence->get_last(), IndexOutOfRangeException);
}