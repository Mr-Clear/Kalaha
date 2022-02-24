#pragma once

#include "AI/AbstractLayer.h"

#include <vector>

class InputLayer : public AbstractLayer
{
public:
    InputLayer(int size);
    InputLayer(std::initializer_list<float> values);

    [[nodiscard]] int outputSize() const override;
    [[nodiscard]] const std::vector<float> values() const;
    [[nodiscard]] float value(int index) const;
    void set(int index, float value);
    void set(const std::initializer_list<float> &values);
    template <typename Iterator>
    void set(Iterator begin, const Iterator &end)
    {
        for (auto i = m_values.begin(); begin != end; ++begin, ++i)
            *i = static_cast<float>(*begin);
    }

private:
    std::vector<float> m_values;
};

