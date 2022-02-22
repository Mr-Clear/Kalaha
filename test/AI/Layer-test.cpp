#include "AI/InputLayer.h"
#include "AI/FullyConnectedLayer.h"
#include "AI/FunctionLayer.h"

#include <gtest/gtest.h>

namespace {
void verifyLayerOut(const AbstractLayer &l, std::initializer_list<float> v)
{
    EXPECT_EQ(l.size(), v.size());
    auto iv = v.begin();
    for (int i = 0; i < l.size(); ++i, ++iv)
    {
        EXPECT_EQ(l[i], *iv) << "at index " << i;
    }
}
}

TEST(LayerTest, testInputLayer)
{
    InputLayer il(6);
    EXPECT_EQ(il.size(), 6);
    EXPECT_EQ(il[4], 0);
    verifyLayerOut(il, {0, 0, 0, 0, 0, 0});
    il[4] = 3;
    EXPECT_EQ(il[4], 3);
    verifyLayerOut(il, {0, 0, 0, 0, 3, 0});
    il.set({1, 2, 3, 4, 5, 6});
    verifyLayerOut(il, {1, 2, 3, 4, 5, 6});

    std::vector<float> vals{6, 5, 4, 3, 2, 1};
    il.set(vals.begin(), vals.end());
    verifyLayerOut(il, {6, 5, 4, 3, 2, 1});

    il = InputLayer{1, 5, 9, 7, 5, 3};
    verifyLayerOut(il, {1, 5, 9, 7, 5, 3});

}

TEST(LayerTest, testFullyConnectedLayer)
{
    InputLayer il = InputLayer{1, 2, 3, 4, 5, 6};
    FullyConnectedLayer fcl{4, il};
    EXPECT_EQ(fcl.gain(2, 5), 1.f / 6);
    EXPECT_EQ(fcl.bias(2), 0);

    fcl.calculate();
    verifyLayerOut(fcl, {3.5, 3.5, 3.5, 3.5});

    fcl.setGains({{0, 1, 2, 3, 4, 5}, {10, 11, 12, 13, 14, 15}, {40, 41, 42, 43, 44, 45}, {30, 31, 32, 33, 34, 35}});
    EXPECT_EQ(fcl.gain(0, 0), 0);
    EXPECT_EQ(fcl.gain(1, 2), 12);
    EXPECT_EQ(fcl.gain(2, 3), 43);
    EXPECT_EQ(fcl.gain(3, 5), 35);
    fcl.calculate();
    verifyLayerOut(fcl, {70, 280, 910, 700});

    fcl.setGains(2, {20, 21, 22, 23, 24, 25});
    EXPECT_EQ(fcl.gain(0, 0), 0);
    EXPECT_EQ(fcl.gain(1, 2), 12);
    EXPECT_EQ(fcl.gain(2, 3), 23);
    EXPECT_EQ(fcl.gain(3, 5), 35);
    fcl.calculate();
    verifyLayerOut(fcl, {70, 280, 490, 700});

    fcl.setGain(3, 5, 45);
    EXPECT_EQ(fcl.gain(0, 0), 0);
    EXPECT_EQ(fcl.gain(1, 2), 12);
    EXPECT_EQ(fcl.gain(2, 3), 23);
    EXPECT_EQ(fcl.gain(3, 5), 45);
    fcl.calculate();
    verifyLayerOut(fcl, {70, 280, 490, 760});

    fcl.setBias({-1, 1, -2, 2});
    EXPECT_EQ(fcl.bias(2), -2);
    fcl.calculate();
    verifyLayerOut(fcl, {69, 281, 488, 762});

    fcl.setBias(2, 5);
    EXPECT_EQ(fcl.bias(2), 5);
    fcl.calculate();
    verifyLayerOut(fcl, {69, 281, 495, 762});
}

TEST(LayerTest, testFullyConnectedLayerModify)
{
    InputLayer il = InputLayer{2, 3, 5, 7};
    FullyConnectedLayer fcl{2, il};
    fcl.setGains({{1, 2, 3, 4}, {5, 6, 7, 8}});
    fcl.setBias({5, -5});
    fcl.calculate();
    verifyLayerOut(fcl, {56, 114});

    fcl.manipulateGain([] (float v) {return v * 2;});
    fcl.calculate();
    verifyLayerOut(fcl, {107, 233});

    fcl.manipulateBias([] (float) {return 2;});
    fcl.calculate();
    verifyLayerOut(fcl, {104, 240});

    fcl.manipulateAll([] (float v) {return v - 1;});
    fcl.calculate();
    verifyLayerOut(fcl, {86, 222});
}

TEST(LayerTest, functionLayer)
{
    InputLayer il = InputLayer{1, 3, 7, 10};
    FunctionLayer fl{il, [] (float v) {return v * v;}};
    EXPECT_EQ(fl.size(), 4);
    verifyLayerOut(fl, {1, 9, 49, 100});
}

TEST(LayerTest, setValuesExceptionTest)
{
    InputLayer il = InputLayer{1, 2, 3, 5};
    FullyConnectedLayer fcl{3, il};

    ASSERT_THROW(il.set({0, 0, 0}), std::length_error);

    ASSERT_THROW(fcl.setGain(1, 4, 0), std::out_of_range);
    ASSERT_THROW(fcl.setGain(-1, 0, 0), std::out_of_range);
    ASSERT_THROW(fcl.setGains(3, {0, 0, 0, 0}), std::out_of_range);
    ASSERT_THROW(fcl.setGains(1, {0, 0}), std::length_error);
    ASSERT_THROW(fcl.setGains({{0, 0, 0, 0}, {0, 0, 0, 0}}), std::length_error);
    ASSERT_THROW(fcl.setGains({{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0}}), std::length_error);

    ASSERT_THROW(fcl.setBias(4, 0), std::out_of_range);
    ASSERT_THROW(fcl.setBias({0, 0}), std::length_error);
}

TEST(LayerTest, relu)
{
    for (int i = -30; i <= 0; i++)
        EXPECT_EQ(relu(i / 10.f), 0);
    for (int i = 0; i < 30; i++)
        EXPECT_EQ(relu(i / 10.f), i / 10.f);
}
