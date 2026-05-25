#include <gtest/gtest.h>
#include "../lazy_sequence/LazySequence.hpp"
#include "../generators/RecurrentGenerator.hpp"

auto counter = [](const MutableArraySequence<int>& sequence) -> int {
    if (sequence.get_length() == 0) {
        return 1;
    }
    return sequence.get_last() + 1;
};

auto function = [](int x) {
    return x * 2;
};

    auto predicate = [](int x) {
        return x % 2 == 0;
    };


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



TEST(lazy_operations_test, finite_map_test) {
    int array[] = {10, 20, 30};
    auto sequence = std::make_shared<LazyInt>(array, 3);

    auto mapped = sequence->map<int>(function);

    ASSERT_EQ(sequence->get_materialized_count(), 0);
    ASSERT_EQ(mapped->get_materialized_count(), 0);

    EXPECT_EQ(mapped->get(1), 40);
    EXPECT_EQ(mapped->get_materialized_count(), 2);
    EXPECT_EQ(sequence->get_materialized_count(), 0);

}

TEST(lazy_operations_test, infinite_map_test) {
    MutableArraySequence<int> cache;
    cache.append(1);

    auto generator = std::make_shared<RecurrentGenerator<int, MutableArraySequence>>(counter, cache);
    auto sequence = std::make_shared<LazyInt>(cache, generator);
    auto mapped = sequence->map<int>(function);

    ASSERT_EQ(sequence->get_length().is_infinite(), 1);
    EXPECT_EQ(sequence->get_materialized_count(), 1);
    
    EXPECT_EQ(mapped->get_length().is_infinite(), 1);
    EXPECT_EQ(mapped->get_materialized_count(), 0);

    EXPECT_EQ(mapped->get(Cardinal(2)), 6);
    EXPECT_EQ(mapped->get_materialized_count(), 3);
    EXPECT_EQ(sequence->get_materialized_count(), 1);

}

TEST(lazy_operations_test, finite_where_test) {

    int array[] = {10, 15, 20};
    auto sequence = std::make_shared<LazyInt>(array, 3);

    auto filtered = sequence->where(predicate);

    ASSERT_EQ(sequence->get_materialized_count(), 0);
    ASSERT_EQ(filtered->get_materialized_count(), 0);

    EXPECT_EQ(filtered->get_length().get_size(), 2);
    EXPECT_EQ(filtered->get(1), 20);
    EXPECT_EQ(filtered->get_materialized_count(), 2);
    EXPECT_EQ(sequence->get_materialized_count(), 0);

}

TEST(lazy_operations_test, infinite_where_test) {
    MutableArraySequence<int> cache;
    auto generator = std::make_shared<RecurrentGenerator<int, MutableArraySequence>>(counter, cache);
    auto sequence = std::make_shared<LazyInt>(cache, generator);
    auto filtered = sequence->where(predicate);

    ASSERT_EQ(sequence->get_length().is_infinite(), 1);
    EXPECT_EQ(sequence->get_materialized_count(), 0);
    
    EXPECT_EQ(filtered->get_length().is_infinite(), 1);
    EXPECT_EQ(filtered->get_materialized_count(), 0);

    EXPECT_EQ(filtered->get(Cardinal(2)), 6);
    EXPECT_EQ(filtered->get_materialized_count(), 3);
    EXPECT_EQ(sequence->get_materialized_count(), 0);
}

TEST(lazy_operations_test, finite_skip_test) {

    int array[] = {10, 15, 20, 25, 30, 35, 40};
    auto sequence = std::make_shared<LazyInt>(array, 7);

    auto skipped = sequence->skip(3);

    ASSERT_EQ(sequence->get_materialized_count(), 0);
    ASSERT_EQ(skipped->get_materialized_count(), 0);

    EXPECT_EQ(skipped->get_length().get_size(), 4);
    EXPECT_EQ(skipped->get(0), 25);
    EXPECT_EQ(skipped->get_materialized_count(), 1);
    EXPECT_EQ(sequence->get_materialized_count(), 0);

}

TEST(lazy_operations_test, infinite_skip_test) {
    MutableArraySequence<int> cache;
    auto generator = std::make_shared<RecurrentGenerator<int, MutableArraySequence>>(counter, cache);
    auto sequence = std::make_shared<LazyInt>(cache, generator);
    auto skipped = sequence->skip(5);

    ASSERT_EQ(sequence->get_length().is_infinite(), 1);
    EXPECT_EQ(sequence->get_materialized_count(), 0);
    
    EXPECT_EQ(skipped->get_length().is_infinite(), 1);
    EXPECT_EQ(skipped->get_materialized_count(), 0);

    EXPECT_EQ(skipped->get(Cardinal(0)), 6);
    EXPECT_EQ(skipped->get_materialized_count(), 1);
    EXPECT_EQ(sequence->get_materialized_count(), 0);
}

TEST(lazy_operations_test, finite_take_test) {

    int array[] = {10, 15, 20, 25, 30, 35, 40};
    auto sequence = std::make_shared<LazyInt>(array, 7);

    auto skipped = sequence->take(3);

    ASSERT_EQ(sequence->get_materialized_count(), 0);
    ASSERT_EQ(skipped->get_materialized_count(), 0);

    EXPECT_EQ(skipped->get_length().get_size(), 3);
    EXPECT_EQ(skipped->get(0), 10);
    EXPECT_EQ(skipped->get_materialized_count(), 1);
    EXPECT_EQ(sequence->get_materialized_count(), 0);

}

TEST(lazy_operations_test, infinite_take_test) {
    MutableArraySequence<int> cache;
    auto generator = std::make_shared<RecurrentGenerator<int, MutableArraySequence>>(counter, cache);
    auto sequence = std::make_shared<LazyInt>(cache, generator);
    auto skipped = sequence->take(5);

    ASSERT_EQ(sequence->get_length().is_infinite(), 1);
    EXPECT_EQ(sequence->get_materialized_count(), 0);
    
    EXPECT_EQ(skipped->get_length().is_infinite(), 0);
    EXPECT_EQ(skipped->get_materialized_count(), 0);

    EXPECT_EQ(skipped->get(Cardinal(0)), 1);
    EXPECT_EQ(skipped->get_materialized_count(), 1);
    EXPECT_EQ(sequence->get_materialized_count(), 0);
}

TEST(lazy_operations_test, finite_concat_test) {
    int array[] = {10, 15, 20, 25, 30, 35, 40};
    auto first = std::make_shared<LazyInt>(array, 7);
    auto second = std::make_shared<LazyInt>(array, 3);

    auto result = first->concat(second);

    ASSERT_EQ(first->get_materialized_count(), 0);
    ASSERT_EQ(result->get_materialized_count(), 0);

    EXPECT_EQ(result->get_length().get_size(), 10);
    EXPECT_EQ(result->get(0), 10);
    EXPECT_EQ(result->get_materialized_count(), 1);
    EXPECT_EQ(first->get_materialized_count(), 0);
}

TEST(lazy_operations_test, infinite_concat_test) {
    MutableArraySequence<int> cache_1;
    MutableArraySequence<int> cache_2;
    auto generator = std::make_shared<RecurrentGenerator<int, MutableArraySequence>>(counter, cache_1);
    auto generator_2 = std::make_shared<RecurrentGenerator<int, MutableArraySequence>>(counter, cache_2);
    auto first = std::make_shared<LazyInt>(cache_1, generator);
    auto second = std::make_shared<LazyInt>(cache_2, generator_2);

    auto result = first->concat(second);

    ASSERT_EQ(result->get_length().is_infinite(), 1);
    EXPECT_EQ(result->get_materialized_count(), 0);

    EXPECT_EQ(result->get(Cardinal(0)), 1);
    EXPECT_THROW(result->get_last(), IndexOutOfRangeException);
    EXPECT_EQ(result->get_materialized_count(), 1);
    EXPECT_EQ(first->get_materialized_count(), 0);
}

TEST(lazy_operations_test, infinite_subsequence_test) {
    MutableArraySequence<int> cache;
    auto generator = std::make_shared<RecurrentGenerator<int, MutableArraySequence>>(counter, cache);
    auto sequence = std::make_shared<LazyInt>(cache, generator);

    auto sub = sequence->get_subsequence(0, 3);

    ASSERT_EQ(sub->get_length().get_size(), 4);
    EXPECT_EQ(sub->get_materialized_count(), 0);

    EXPECT_EQ(sub->get(Cardinal(0)), 1);
    EXPECT_EQ(sub->get_last(), 4);
    EXPECT_EQ(sub->get_materialized_count(), 4);
    EXPECT_EQ(sequence->get_materialized_count(), 0);
}

TEST(lazy_operations_test, finite_subsequence_test) {
    int array[] = {10, 15, 20, 25, 30, 35, 40};
    auto sequence = std::make_shared<LazyInt>(array, 7);

    auto sub = sequence->get_subsequence(0, 3);

    ASSERT_EQ(sequence->get_materialized_count(), 0);
    ASSERT_EQ(sub->get_materialized_count(), 0);

    EXPECT_EQ(sub->get_length().get_size(), 4);
    EXPECT_EQ(sub->get(0), 10);
    EXPECT_EQ(sub->get_materialized_count(), 1);
    EXPECT_EQ(sequence->get_materialized_count(), 0);
}