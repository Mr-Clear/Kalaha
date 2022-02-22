#pragma once

#include "AI/InputLayer.h"
#include "AI/InnerLayer.h"

#include <functional>

class Ai
{
public:
    explicit Ai(const InputLayer &inputLayer);

    [[nodiscard]] int size() const;
    [[nodiscard]] const AbstractLayer &lastLayer() const;
    float operator[](int index) const;

    void addLayer(InnerLayer &layer);
    void calculate();
    void mutate(float stddev);

private:
    const InputLayer &m_inputLayer;
    std::vector<std::reference_wrapper<InnerLayer>> m_innerLayers;
};

