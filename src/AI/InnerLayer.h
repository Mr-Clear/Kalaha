#pragma once

#include <AI/AbstractLayer.h>

#include <vector>

class InnerLayer : public AbstractLayer
{
public:
    InnerLayer(int inputSize);
    [[nodiscard]] int inputSize() const;

    virtual std::vector<float> calculate(const std::vector<float> &input) = 0;

    [[nodiscard]] virtual InnerLayer *clone() const = 0;

private:
    const int m_inputSize;
};
