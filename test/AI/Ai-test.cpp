#include "AI/Ai.h"
#include "AI/InputLayer.h"
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
    Ai ai{{1, 2, 3, 4, 5, 6, 7, 8, 9}};
    EXPECT_EQ(ai.outputSize(), 9);
    EXPECT_EQ(ai.inputLayer(), InputLayer({1, 2, 3, 4, 5, 6, 7, 8, 9}));
    verify(ai.calculate(), {1, 2, 3, 4, 5, 6, 7, 8, 9});
}

TEST(AiTest, testTwoLayers)
{
    Ai ai{{1, 2, 3}};
    EXPECT_EQ(ai.outputSize(), 3);
    FullyConnectedLayer *fcl = new FullyConnectedLayer{3, 2};
    fcl->setGains(1, {1, 1, 1});
    ai.addLayer(fcl);
    EXPECT_EQ(ai.outputSize(), 2);

    auto out = ai.calculate();
    verify(out, {2, 6});
}

TEST(AiTest, copyConstructor)
{
    Ai ai{{1, 2, 3}};
    FullyConnectedLayer *fcl = new FullyConnectedLayer{3, 2};
    fcl->setGains(1, {1, 1, 1});
    ai.addLayer(fcl);
    Ai copy{ai};

    auto out = copy.calculate();
    verify(out, {2, 6});
}

TEST(AiTest, assignment)
{
    Ai ai{{1, 2, 3}};
    FullyConnectedLayer *fcl = new FullyConnectedLayer{3, 2};
    fcl->setGains(1, {1, 1, 1});
    ai.addLayer(fcl);
    Ai copy{2};
    copy = ai;

    auto out = copy.calculate();
    verify(out, {2, 6});

    Ai ai2{{4, 5, 6}};
    fcl = new FullyConnectedLayer{3, 2};
    fcl->setGains(0, {5, 8, 6});
    fcl->setGains(1, {0, 1, 2});
    ai2.addLayer(fcl);

    copy = ai2;
    out = copy.calculate();
    verify(out, {96, 17});
}
