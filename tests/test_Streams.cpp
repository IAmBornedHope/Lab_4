#include <gtest/gtest.h>
#include "../lazy_sequence/LazySequence.hpp"
#include "../generators/ContainerGenerator.hpp"
#include "../streams/LazyInputStream.hpp"
#include "../streams/SequenceOutputStream.hpp"

auto counter_function = [](const MutableArraySequence<int>& sequence) -> int {
    if (sequence.get_length() == 0) {
        return 1;
    }
    return sequence.get_last() + 1;
};

using LazyInt = LazySequence<int, MutableArraySequence>;

TEST(stream_constructor, stream_from_container_test) {
    int array[] = {10, 20, 30, 40, 50, 60};
    MutableArraySequence<int> sequence(array, 6);
    LazyInputStream<int, MutableArraySequence> stream(sequence);

    ASSERT_EQ(stream.has_next(), 1);
    EXPECT_EQ(stream.read(), 10);
    EXPECT_EQ(stream.read(), 20);
    EXPECT_EQ(stream.read(), 30);
    EXPECT_EQ(stream.read(), 40);
    EXPECT_EQ(stream.read(), 50);
    EXPECT_EQ(stream.read(), 60);
    EXPECT_EQ(stream.has_next(), 0);

}

TEST(stream_constructor, sequence_output_test) {
    auto out = std::make_shared<MutableArraySequence<int>>();
    auto stream = SequenceOutputStream<int>(out);

    stream.write(1);
    stream.write(2);
    stream.write(3);

    ASSERT_EQ(out->get_length(), 3);
    EXPECT_EQ(out->get(0), 1);
    EXPECT_EQ(out->get(1), 2);
    EXPECT_EQ(out->get(2), 3);

}