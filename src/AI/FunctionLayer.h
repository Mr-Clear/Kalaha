#pragma once

#include "AI/AbstractLayer.h"

#include <functional>

class FunctionLayer : public AbstractLayer
{
public:
    FunctionLayer(int inputSize, const std::function<float(float)> &fn);
    [[nodiscard]] FunctionLayer *clone() const override;

    [[nodiscard]] int outputSize() const override;
    std::vector<float> calculate(const std::vector<float> &input) override;

private:
    std::function<float(float)> m_fn;
};

extern const std::function<float(float)> relu;
extern const std::function<float(float)> gelu;
