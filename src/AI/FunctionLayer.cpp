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

FunctionLayer::FunctionLayer(const AbstractLayer &predecessor, const std::function<float(float)> &fn) :
    InnerLayer{predecessor},
    m_fn{fn}
{ }

int FunctionLayer::size() const
{
    return predecessor().size();
}

float FunctionLayer::operator[](int index) const
{
    return m_fn(predecessor()[index]);
}
