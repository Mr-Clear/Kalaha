#pragma once

#include "AI/InnerLayer.h"

#include <functional>

class FunctionLayer : public InnerLayer
{
public:
    FunctionLayer(const AbstractLayer &predecessor, const std::function<float(float)> &fn);

    [[nodiscard]] int size() const override;
    [[nodiscard]] float operator[](int index) const override;
    void calculate() override { };

private:
    std::function<float(float)> m_fn;
};

extern const std::function<float(float)> relu;
extern const std::function<float(float)> gelu;
