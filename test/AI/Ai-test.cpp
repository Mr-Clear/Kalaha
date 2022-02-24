#include "AI/Ai.h"
#include "AI/FullyConnectedLayer.h"

#include <gtest/gtest.h>

namespace {
void verify(const std::vector<float> &v, const std::initializer_list<float> &ex)
{
    EXPECT_EQ(v.size(), ex.size());
    auto iv = ex.begin();
    for (int i = 0; i < ex.size(); ++i, ++iv)
    {
        EXPECT_EQ(v.at(i), *iv) << "at index " << i;
    }
}
}

TEST(AiTest, testInputOnly)
{
    Ai ai;
    EXPECT_EQ(ai.outputSize(), 0);
    verify(ai.calculate({1, 2, 3, 4, 5, 6, 7, 8, 9}), {1, 2, 3, 4, 5, 6, 7, 8, 9});
}

TEST(AiTest, testTwoLayers)
{
    Ai ai;
    FullyConnectedLayer *fcl = new FullyConnectedLayer{3, 2};
    fcl->setGains(1, {1, 1, 1});
    ai.addLayer(fcl);
    EXPECT_EQ(ai.outputSize(), 2);

    auto out = ai.calculate({1, 2, 3});
    verify(out, {2, 6});
}

TEST(AiTest, copyConstructor)
{
    Ai ai;
    FullyConnectedLayer *fcl = new FullyConnectedLayer{3, 2};
    fcl->setGains(1, {1, 1, 1});
    ai.addLayer(fcl);
    Ai copy{ai};

    auto out = copy.calculate({1, 2, 3});
    verify(out, {2, 6});
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
    verify(out, {2, 6});

    Ai ai2;
    fcl = new FullyConnectedLayer{3, 2};
    fcl->setGains(0, {5, 8, 6});
    fcl->setGains(1, {0, 1, 2});
    ai2.addLayer(fcl);

    copy = ai2;
    out = copy.calculate({4, 5, 6});
    verify(out, {96, 17});
}

TEST(AiTest, wrongInputException)
{
    Ai ai;
    FullyConnectedLayer *fcl = new FullyConnectedLayer{3, 2};
    fcl->setGains(1, {1, 1, 1});
    ai.addLayer(fcl);
    ASSERT_THROW(ai.calculate({0, 0}), std::invalid_argument);
}
