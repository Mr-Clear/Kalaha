#include "AI/FullyConnectedLayer.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::ElementsAre;

TEST(FullyConnectedLayerTest, set)
{
    std::vector<float> input{1, 2, 3, 4, 5, 6};
    FullyConnectedLayer fcl{6, 4};
    EXPECT_EQ(fcl.gain(2, 5), 1.f / 6);
    EXPECT_EQ(fcl.bias(2), 0);

    auto output = fcl.calculate(input);
    EXPECT_THAT(output, ElementsAre(3.5, 3.5, 3.5, 3.5));

    fcl.setGains({{0, 1, 2, 3, 4, 5}, {10, 11, 12, 13, 14, 15}, {40, 41, 42, 43, 44, 45}, {30, 31, 32, 33, 34, 35}});
    EXPECT_EQ(fcl.gain(0, 0), 0);
    EXPECT_EQ(fcl.gain(1, 2), 12);
    EXPECT_EQ(fcl.gain(2, 3), 43);
    EXPECT_EQ(fcl.gain(3, 5), 35);
    output = fcl.calculate(input);
    EXPECT_THAT(output, ElementsAre(70, 280, 910, 700));

    fcl.setGains(2, {20, 21, 22, 23, 24, 25});
    EXPECT_EQ(fcl.gain(0, 0), 0);
    EXPECT_EQ(fcl.gain(1, 2), 12);
    EXPECT_EQ(fcl.gain(2, 3), 23);
    EXPECT_EQ(fcl.gain(3, 5), 35);
    output = fcl.calculate(input);
    EXPECT_THAT(output, ElementsAre(70, 280, 490, 700));

    fcl.setGain(3, 5, 45);
    EXPECT_EQ(fcl.gain(0, 0), 0);
    EXPECT_EQ(fcl.gain(1, 2), 12);
    EXPECT_EQ(fcl.gain(2, 3), 23);
    EXPECT_EQ(fcl.gain(3, 5), 45);
    output = fcl.calculate(input);
    EXPECT_THAT(output, ElementsAre(70, 280, 490, 760));

    fcl.setBias({-1, 1, -2, 2});
    EXPECT_EQ(fcl.bias(2), -2);
    output = fcl.calculate(input);
    EXPECT_THAT(output, ElementsAre(69, 281, 488, 762));

    fcl.setBias(2, 5);
    EXPECT_EQ(fcl.bias(2), 5);
    output = fcl.calculate(input);
    EXPECT_THAT(output, ElementsAre(69, 281, 495, 762));
}

TEST(FullyConnectedLayerTest, modify)
{
    std::vector<float> input{2, 3, 5, 7};
    FullyConnectedLayer fcl{4, 2};
    fcl.setGains({{1, 2, 3, 4}, {5, 6, 7, 8}});
    fcl.setBias({5, -5});
    auto output = fcl.calculate(input);
    EXPECT_THAT(output, ElementsAre(56, 114));

    fcl.manipulateGain([] (float v) {return v * 2;});
    output = fcl.calculate(input);
    EXPECT_THAT(output, ElementsAre(107, 233));

    fcl.manipulateBias([] (float) {return 2;});
    output = fcl.calculate(input);
    EXPECT_THAT(output, ElementsAre(104, 240));

    fcl.manipulateAll([] (float v) {return v - 1;});
    output = fcl.calculate(input);
    EXPECT_THAT(output, ElementsAre(86, 222));
}

TEST(FullyConnectedLayerTest, setValuesExceptionTest)
{
    FullyConnectedLayer fcl{4, 3};
    ASSERT_THROW(fcl.setGain(1, 4, 0), std::out_of_range);
    ASSERT_THROW(fcl.setGain(-1, 0, 0), std::out_of_range);
    ASSERT_THROW(fcl.setGains(3, {0, 0, 0, 0}), std::out_of_range);
    ASSERT_THROW(fcl.setGains(1, {0, 0}), std::length_error);
    ASSERT_THROW(fcl.setGains({{0, 0, 0, 0}, {0, 0, 0, 0}}), std::length_error);
    ASSERT_THROW(fcl.setGains({{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}}), std::length_error);

    ASSERT_THROW(fcl.setBias(4, 0), std::out_of_range);
    ASSERT_THROW(fcl.setBias({0, 0}), std::length_error);
}
