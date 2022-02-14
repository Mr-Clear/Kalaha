#pragma once

#include  <random>
#include  <iterator>

namespace Tools
{

template<typename I, typename RandomGenerator>
I selectRandomItem(I begin, I end, RandomGenerator& gen)
{
    std::uniform_int_distribution<> dis(0, std::distance(begin, end) - 1);
    std::advance(begin, dis(gen));
    return begin;
}

template<typename I>
I selectRandomItem(I begin, I end)
{
    static std::random_device rnd;
    static std::mt19937 gen(rnd());
    return selectRandomItem(begin, end, gen);
}
};

