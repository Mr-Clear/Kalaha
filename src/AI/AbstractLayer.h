#pragma once

#include <vector>

class AbstractLayer
{
public:
public:
    AbstractLayer(int inputSize);
    virtual ~AbstractLayer() = default;

    [[nodiscard]] int inputSize() const;
    [[nodiscard]] virtual int outputSize() const = 0;

    virtual std::vector<float> calculate(const std::vector<float> &input) = 0;

    [[nodiscard]] virtual AbstractLayer *clone() const = 0;

private:
    const int m_inputSize;
};

