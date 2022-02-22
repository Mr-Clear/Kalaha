#include "InputLayer.h"

#include <stdexcept>

InputLayer::InputLayer(int size) :
    m_values(size, 0.f)
{ }

InputLayer::InputLayer(std::initializer_list<float> values)
{
    m_values = values;
}

int InputLayer::size() const
{
    return m_values.size();
}

float &InputLayer::operator [](int index)
{
    return m_values.at(index);
}

float InputLayer::operator [](int index) const
{
    return m_values.at(index);
}

void InputLayer::set(const std::initializer_list<float> &values)
{
    if (values.size() != size())
        throw std::length_error{"Input values size must be " + std::to_string(size()) + " but is " + std::to_string(values.size()) + "."};
    set(values.begin(), values.end());
}
