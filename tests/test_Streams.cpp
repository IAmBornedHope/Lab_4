#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include "../lazy_sequence/LazySequence.hpp"
#include "../generators/ContainerGenerator.hpp"
#include "../streams/LazyInputStream.hpp"
#include "../streams/SequenceOutputStream.hpp"
#include "../streams/SequenceInputStream.hpp"
#include "../streams/StringInputStream.hpp"
#include "../streams/FileInputStream.hpp"
#include "../streams/StreamInputStream.hpp"
#include "../streams/FileOutputStream.hpp"
#include "../streams/StreamOutputStream.hpp"

auto counter_function = [](const MutableArraySequence<int>& sequence) -> int {
    if (sequence.get_length() == 0) {
        return 1;
    }
    return sequence.get_last() + 1;
};

using LazyInt = LazySequence<int, MutableArraySequence>;

TEST(lazystream_constructor, stream_from_container_test) {
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

TEST(lazystream_constructor, sequence_output_test) {
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

TEST(sequence_input_stream, stream_from_sequence_test) {
    int array[] = {1, 2, 3, 4, 5};
    auto sequence = std::make_shared<MutableArraySequence<int>>(array, 5);
    SequenceInputStream<int> stream(sequence);

    ASSERT_EQ(stream.has_next(), 1);
    EXPECT_EQ(stream.read(), 1);
    EXPECT_EQ(stream.read(), 2);
    EXPECT_EQ(stream.read(), 3);
    EXPECT_EQ(stream.read(), 4);
    EXPECT_EQ(stream.read(), 5);
    EXPECT_EQ(stream.has_next(), 0);
}

TEST(stream_input_stream, stream_from_stream_test) {
    int array[] = {1, 2, 3, 4, 5};
    auto sequence = std::make_shared<MutableArraySequence<int>>(array, 5);
    auto stream = std::make_shared<SequenceInputStream<int>>(sequence);

    StreamInputStream<int> new_stream(stream);

    ASSERT_EQ(new_stream.has_next(), 1);
    EXPECT_EQ(new_stream.read(), 1);
    EXPECT_EQ(new_stream.read(), 2);
    EXPECT_EQ(new_stream.read(), 3);
    EXPECT_EQ(new_stream.read(), 4);
    EXPECT_EQ(new_stream.read(), 5);
    ASSERT_EQ(new_stream.has_next(), 0);

}

TEST(string_input_stream, string_input_int_test) {
    auto stream = std::make_shared<StringInputStream<int>>("1 2 3", Deserializers::int_deserializer(), " ");

    ASSERT_EQ(stream->has_next(), 1);
    EXPECT_EQ(stream->read(), 1);
    EXPECT_EQ(stream->read(), 2);
    EXPECT_EQ(stream->read(), 3);
    ASSERT_EQ(stream->has_next(), 0);
}

TEST(string_input_stream, string_input_double_test) {
    auto stream = std::make_shared<StringInputStream<double>>("1.5, 2.5, 3.5", Deserializers::double_deserializer(), ", ");

    ASSERT_EQ(stream->has_next(), 1);
    EXPECT_NEAR(stream->read(), 1.5, 1e-6);
    EXPECT_NEAR(stream->read(), 2.5, 1e-6);
    EXPECT_NEAR(stream->read(), 3.5, 1e-6);
    ASSERT_EQ(stream->has_next(), 0);
}

TEST(file_input_stream, stream_from_file_int_test) {

    const char* filename = "test_int_space.txt";
    std::ofstream out(filename);
    out << "1 2 3 4 5";
    out.close();


    auto stream = std::make_shared<FileInputStream<int>>(filename, Deserializers::int_deserializer(), " ");
    ASSERT_EQ(stream->has_next(), 1);
    EXPECT_EQ(stream->read(), 1);
    EXPECT_EQ(stream->read(), 2);
    EXPECT_EQ(stream->read(), 3);
    EXPECT_EQ(stream->read(), 4);
    EXPECT_EQ(stream->read(), 5);
    ASSERT_EQ(stream->has_next(), 0);

    std::remove(filename);
}

TEST(file_input_stream, stream_from_file_double_test) {

    const char* filename = "test_double.txt";
    std::ofstream out(filename);
    out << "1.5, 2.5, 3.5";
    out.close();

    auto stream = std::make_shared<FileInputStream<double>>(filename, Deserializers::double_deserializer(), ", ");
    ASSERT_EQ(stream->has_next(), 1);
    EXPECT_NEAR(stream->read(), 1.5, 1e-9);
    EXPECT_NEAR(stream->read(), 2.5, 1e-9);
    EXPECT_NEAR(stream->read(), 3.5, 1e-9);
    ASSERT_EQ(stream->has_next(), 0);

    std::remove(filename);
}

TEST(stream_output_stream, stream_from_sequence_out_stream_test) {
    auto sequence = std::make_shared<MutableArraySequence<int>>();
    auto out = std::make_shared<SequenceOutputStream<int>>(sequence);
    
    auto stream = std::make_shared<StreamOutputStream<int>>(out);

    stream->write(100);
    stream->write(200);

    EXPECT_EQ(sequence->get_length(), 2);
    EXPECT_EQ(sequence->get(0), 100);
    EXPECT_EQ(sequence->get(1), 200);
}