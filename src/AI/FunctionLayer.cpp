#include "FunctionLayer.h"

#include <cmath>

const std::function<float(float)> relu = [] (float v)
{
    return v <= 0 ? 0 : v;
};

const std::function<float(float)> gelu = [] (float v)
{
    return v * erfc(-v / sqrt(2)) / 2.f;
};

FunctionLayer::FunctionLayer(int inputSize, const std::function<float(float)> &fn) :
    AbstractLayer{inputSize},
    m_fn{fn}
{ }

FunctionLayer *FunctionLayer::clone() const
{
    return new FunctionLayer(*this);
}

int FunctionLayer::outputSize() const
{
    return inputSize();
}

std::vector<float> FunctionLayer::calculate(const std::vector<float> &input)
{
    std::vector<float> output;
    output.reserve(input.size());
    for (float i : input)
            output.emplace_back(m_fn(i));
    return output;
}
