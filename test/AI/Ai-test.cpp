#include "AI/Ai.h"
#include "AI/FullyConnectedLayer.h"
#include "AI/FunctionLayer.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using nlohmann::json;
using testing::ElementsAre;

TEST(AiTest, testInputOnly)
{
    Ai ai;
    EXPECT_EQ(ai.outputSize(), -1);
    EXPECT_THAT(ai.calculate({1, 2, 3, 4, 5, 6, 7, 8, 9}), ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 9));
}

TEST(AiTest, testTwoLayers)
{
    Ai ai;
    FullyConnectedLayer *fcl = new FullyConnectedLayer{3, 2};
    fcl->setGains(1, {1, 1, 1});
    ai.addLayer(fcl);
    EXPECT_EQ(ai.outputSize(), 2);

    auto out = ai.calculate({1, 2, 3});
    EXPECT_THAT(out, ElementsAre(2, 6));
}

TEST(AiTest, copyConstructor)
{
    Ai ai;
    FullyConnectedLayer *fcl = new FullyConnectedLayer{3, 2};
    fcl->setGains(1, {1, 1, 1});
    ai.addLayer(fcl);
    Ai copy{ai};

    auto out = copy.calculate({1, 2, 3});
    EXPECT_THAT(out, ElementsAre(2, 6));
}

TEST(AiTest, assignment)
{
    Ai ai;
    FullyConnectedLayer *fcl = new FullyConnectedLayer{3, 2};
    fcl->setGains(1, {1, 1, 1});
    ai.addLayer(fcl);
    Ai copy;
    copy = ai;

    auto out = copy.calculate({1, 2, 3});
    EXPECT_THAT(out, ElementsAre(2, 6));

    Ai ai2;
    fcl = new FullyConnectedLayer{3, 2};
    fcl->setGains(0, {5, 8, 6});
    fcl->setGains(1, {0, 1, 2});
    ai2.addLayer(fcl);

    copy = ai2;
    out = copy.calculate({4, 5, 6});
    EXPECT_THAT(out, ElementsAre(96, 17));
}

TEST(AiTest, wrongInputException)
{
    Ai ai;
    FullyConnectedLayer *fcl = new FullyConnectedLayer{3, 2};
    fcl->setGains(1, {1, 1, 1});
    ai.addLayer(fcl);
    EXPECT_THROW(auto a = ai.calculate({0, 0}), std::invalid_argument);
}

TEST(AiTest, serialize)
{
    Ai ai;
    EXPECT_TRUE(dynamic_cast<Serializable*>(&ai));
    ai.addLayer(new FullyConnectedLayer{3, 2});
    ai.addLayer(FunctionLayer::GELU.clone());
    ai.addLayer(new FullyConnectedLayer{2, 1});
    const float gain = 1 / 3.f;
    const json out = ai.toJson();
    json exp{{"layers",  {{{"FullyConnectedLayer", {{"gains", {{gain, gain, gain}, {gain, gain, gain}}},
                                                    {"biases", {0., 0.}}}}},
                          {{"FunctionLayer", "GELU"}},
                          {{"FullyConnectedLayer", {{"gains", {{.5, .5}}},
                                                    {"biases", {0.}}}}}}}};
    EXPECT_EQ(out, exp);
}

TEST(AiTest, deserialize)
{
    Ai ai;
    ai.fromJson({{"layers",  {{{"FullyConnectedLayer", {{"gains", {{1, 2, 3}, {4, 5, 6}}},
                                                        {"biases", {7, 8}}}}},
                              {{"FunctionLayer", "RELU"}},
                              {{"FullyConnectedLayer", {{"gains", {{15, 10}}},
                                                        {"biases", {11}}}}}}}});
    const auto out = ai.calculate({-1, -2, -3});
    EXPECT_THAT(out, ElementsAre(11));
}

TEST(AiTest, deserializeErrors)
{
    Ai ai;
    EXPECT_THROW(ai.fromJson({}), std::invalid_argument);
    EXPECT_THROW(ai.fromJson({"A", 1}), std::invalid_argument);
    EXPECT_THROW(ai.fromJson({"layers", {"A", 1}}), std::invalid_argument);
}
