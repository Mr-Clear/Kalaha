#pragma once

#include "AI/AbstractLayer.h"

#include <vector>

class InputLayer : public AbstractLayer
{
public:
    InputLayer(int size);
    InputLayer(std::initializer_list<float> values);

    [[nodiscard]] int size() const override;
    float &operator[](int index);
    float operator[](int index) const override;
    void set(const std::initializer_list<float> &values);
    template <typename Iterator>
    void set(Iterator begin, const Iterator &end)
    {
        for (auto i = m_values.begin(); begin != end; ++begin, ++i)
        {
            *i = *begin;
        }
    }

private:
    std::vector<float> m_values;
};

