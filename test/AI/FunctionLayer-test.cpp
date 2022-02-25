#include "AI/FunctionLayer.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(FunctionLayerTest, functionLayer)
{
    std::vector<float> input{1, 3, 7, 10};
    FunctionLayer fl{4, [] (float v) {return v * v;}};
    EXPECT_EQ(fl.outputSize(), 4);
    auto output = fl.calculate(input);
    EXPECT_THAT(output,::testing::ElementsAre(1, 9, 49, 100));
}

TEST(FunctionLayerTest, relu)
{
    for (int i = -30; i <= 0; ++i)
        EXPECT_EQ(relu(i / 10.f), 0);
    for (int i = 0; i < 30; ++i)
        EXPECT_EQ(relu(i / 10.f), i / 10.f);
}
