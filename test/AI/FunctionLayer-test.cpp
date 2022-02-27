#include "AI/FunctionLayer.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(FunctionLayerTest, functionLayer)
{
    FunctionLayer fl{"Square", [ ] (float v) {return v * v;}};
    EXPECT_EQ(fl.outputSize(), -1);
    auto output = fl.calculate({1, 3, 7, 10});
    EXPECT_THAT(output, testing::ElementsAre(1, 9, 49, 100));
}

TEST(FunctionLayerTest, relu)
{
    FunctionLayer l = FunctionLayer::RELU;
    const std::vector<float> o = l.calculate({-3, -2, -1, -0.1, 0, 0.1, 1, 2, 3});
    EXPECT_THAT(o, testing::ElementsAre(0, 0, 0, 0, 0, 0.1, 1, 2, 3));
}

TEST(FunctionLayerTest, gelu)
{
    FunctionLayer l = FunctionLayer::GELU;
    const std::vector<float> o = l.calculate({-20, 0, 10});
    EXPECT_THAT(o, testing::ElementsAre(0, 0, 10));
}

TEST(FunctionLayerTest, serialize)
{
    FunctionLayer l = FunctionLayer::GELU;
    auto j = l.toJson();
    nlohmann::json x{{"FunctionLayer", "GELU"}};
    EXPECT_EQ(j, x);
}

TEST(FunctionLayerTest, deserialize)
{
    FunctionLayer l = FunctionLayer::GELU;
    l.fromJson({{"FunctionLayer", "RELU"}});
    const std::vector<float> o = l.calculate({-1, 0, 1});
    EXPECT_THAT(o, testing::ElementsAre(0, 0, 1));
}

TEST(FunctionLayerTest, deserializeErrors)
{
    FunctionLayer l = FunctionLayer::GELU;
    EXPECT_THROW(l.fromJson({}), std::invalid_argument);
    EXPECT_THROW(l.fromJson({{"FunctionLayer", 1}}), std::invalid_argument);
    EXPECT_THROW(l.fromJson({{"FunctionLayer", "Foo"}}), std::invalid_argument);
}
