#include "InputLayer.h"

#include <stdexcept>

InputLayer::InputLayer(int size) :
    m_values(size, 0.f)
{ }

InputLayer::InputLayer(std::initializer_list<float> values)
{
    m_values = values;
}

int InputLayer::outputSize() const
{
    return m_values.size();
}

const std::vector<float> InputLayer::values() const
{
    return m_values;
}

float InputLayer::value(int index) const
{
    return m_values.at(index);
}

void InputLayer::set(int index, float value)
{
    m_values.at(index) = value;
}

void InputLayer::set(const std::initializer_list<float> &values)
{
    if (values.size() != outputSize())
        throw std::length_error{"Input values size must be " + std::to_string(outputSize()) + " but is " + std::to_string(values.size()) + "."};
    set(values.begin(), values.end());
}
