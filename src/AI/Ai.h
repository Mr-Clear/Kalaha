#pragma once

#include "AI/AbstractLayer.h"

#include <memory>
#include <optional>

class Ai
{
public:
    explicit Ai() = default;
    Ai(const Ai &o);
    Ai &operator=(const Ai &o);

    [[nodiscard]] int outputSize() const;
    [[nodiscard]] const AbstractLayer &lastLayer() const;

    void addLayer(AbstractLayer *layer);
    void addLayer(std::unique_ptr<AbstractLayer> &layer);
    std::vector<float> calculate(const std::vector<float> &input);
    void mutate(float stddev);

private:
    std::vector<std::unique_ptr<AbstractLayer>> m_AbstractLayers;
};

