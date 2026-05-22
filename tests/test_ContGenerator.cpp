#include <gtest/gtest.h>
#include "../generators/ContainerGenerator.hpp"
#include "../libs/Lab_3/exceptions/Option.hpp"
#include "../libs/Lab_3/array_sequence/MutableArraySequence.hpp"

TEST(container_generator, basic_constructor_test) {
    int array[] = {1, 2, 10};
    MutableArraySequence<int> sequence(array, 3);
    ContainerGenerator<int, MutableArraySequence> generator(sequence);

    ASSERT_EQ(generator.has_next(), 1);
    EXPECT_EQ(generator.size().get_size(), 3);

}

TEST(container_generator, basic_iteration_test) {
    int array[] = {1, 2, 3, 4, 5};
    MutableArraySequence<int> sequence(array, 5);
    ContainerGenerator<int, MutableArraySequence> generator(sequence);
    
    EXPECT_EQ(generator.get_next(), 1);
    EXPECT_EQ(generator.get_position(), 1);
    EXPECT_EQ(generator.get_next(), 2);
    EXPECT_EQ(generator.get_position(), 2);
    EXPECT_EQ(generator.get_next(), 3);
    EXPECT_EQ(generator.get_position(), 3);
    EXPECT_EQ(generator.get_next(), 4);
    EXPECT_EQ(generator.get_position(), 4);
    EXPECT_EQ(generator.get_next(), 5);
    EXPECT_EQ(generator.get_position(), 5);
}

TEST(container_generator, sizers_test) {
    int array[] = {1, 2, 3, 4, 5};
    MutableArraySequence<int> sequence(array, 5);
    ContainerGenerator<int, MutableArraySequence> generator(sequence);

    ASSERT_EQ(generator.size().get_size(), 5);
    EXPECT_EQ(generator.get_position(), 0);
    generator.get_next();
    EXPECT_EQ(generator.get_position(), 1);
    EXPECT_EQ(generator.size().get_size(), 5);
}

TEST(container_generator, index_out_exceptions) {
    int array[] = {1, 10};
    MutableArraySequence<int> sequence(array, 2);
    ContainerGenerator<int, MutableArraySequence> generator(sequence);

    EXPECT_EQ(generator.get_next(), 1);
    EXPECT_EQ(generator.get_next(), 10);
    EXPECT_THROW(generator.get_next(), IndexOutOfRangeException);
}

TEST(container_generator, has_next_const_test) {
    int array[] = {1};
    MutableArraySequence<int> sequence(array, 1);
    ContainerGenerator<int, MutableArraySequence> generator(sequence);
    ASSERT_EQ(generator.size(), 1);
    EXPECT_EQ(generator.get_position(), 0);
    EXPECT_EQ(generator.has_next(), 1);
    EXPECT_EQ(generator.get_position(), 0);
    EXPECT_EQ(generator.size(), 1);
}