#include <gtest/gtest.h>
#include "../lazy_sequence/LazySequence.hpp"
#include "../generators/ContainerGenerator.hpp"
#include "../streams/LazyInputStream.hpp"
#include "../streams/SequenceOutputStream.hpp"
#include "../stream_sort/StreamSorter.hpp"

TEST(heap_sort, ascending_sort_test) {
    int array[] = {1, 5, 2, 4, 6, 3};
    MutableArraySequence<int> sequence(array, 6);
    LazyInputStream<int, MutableArraySequence> stream(sequence);

    auto out = std::make_shared<MutableArraySequence<int>>();
    auto out_stream = SequenceOutputStream<int>(out);

    sort_stream<int>(stream, out_stream, SortingOrder::ascending);

    ASSERT_EQ(out->get_length(), 6);
    EXPECT_EQ(out->get(0), 1);
    EXPECT_EQ(out->get(1), 2);
    EXPECT_EQ(out->get(2), 3);
    EXPECT_EQ(out->get(3), 4);
    EXPECT_EQ(out->get(4), 5);
    EXPECT_EQ(out->get(5), 6);

}

TEST(heap_sort, descending_sort_test) {
    int array[] = {1, 5, 2, 4, 6, 3};
    MutableArraySequence<int> sequence(array, 6);
    LazyInputStream<int, MutableArraySequence> stream(sequence);

    auto out = std::make_shared<MutableArraySequence<int>>();
    auto out_stream = SequenceOutputStream<int>(out);

    sort_stream<int>(stream, out_stream, SortingOrder::descending);

    ASSERT_EQ(out->get_length(), 6);
    EXPECT_EQ(out->get(0), 6);
    EXPECT_EQ(out->get(1), 5);
    EXPECT_EQ(out->get(2), 4);
    EXPECT_EQ(out->get(3), 3);
    EXPECT_EQ(out->get(4), 2);
    EXPECT_EQ(out->get(5), 1);

}