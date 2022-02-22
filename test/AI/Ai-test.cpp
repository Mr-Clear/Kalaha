#include "AI/Ai.h"
#include "AI/InputLayer.h"
#include "AI/FullyConnectedLayer.h"

#include <gtest/gtest.h>

namespace {
void verify(const Ai &ai, const std::initializer_list<float> &v)
{
    EXPECT_EQ(ai.size(), v.size());
    auto iv = v.begin();
    for (int i = 0; i < ai.size(); ++i, ++iv)
    {
        EXPECT_EQ(ai[i], *iv) << "at index " << i;
    }
}
}

TEST(AiTest, testInputOnly)
{
    InputLayer il(9);
    Ai ai{il};
    EXPECT_EQ(&ai.lastLayer(), &il);
    EXPECT_EQ(ai.size(), 9);
    il.set({1, 2, 3, 4, 5, 6, 7, 8, 9});
    EXPECT_EQ(ai[1], 2);
    verify(ai, {1, 2, 3, 4, 5, 6, 7, 8, 9});
}

TEST(AiTest, testTwoLayers)
{
    InputLayer il(3);
    Ai ai{il};
    il.set({1, 2, 3});
    EXPECT_EQ(ai.size(), 3);
    FullyConnectedLayer fcl{2, il};
    fcl.setGains(1, {1, 1, 1});
    ai.addLayer(fcl);
    EXPECT_EQ(ai.size(), 2);

    ai.calculate();
    verify(ai, {2, 6});
}
