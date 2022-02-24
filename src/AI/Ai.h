#pragma once

#include "AI/InputLayer.h"
#include "AI/InnerLayer.h"

#include <memory>

class Ai
{
public:
    explicit Ai(const InputLayer &inputLayer);
    Ai(const Ai &o);
    Ai &operator=(const Ai &o);

    [[nodiscard]] InputLayer &inputLayer();
    [[nodiscard]] const InputLayer &inputLayer() const;
    [[nodiscard]] int outputSize() const;
    [[nodiscard]] const AbstractLayer &lastLayer() const;

    void addLayer(InnerLayer *layer);
    void addLayer(std::unique_ptr<InnerLayer> &layer);
    std::vector<float> calculate();
    void mutate(float stddev);

private:
    InputLayer m_inputLayer;
    std::vector<std::unique_ptr<InnerLayer>> m_innerLayers;
};

