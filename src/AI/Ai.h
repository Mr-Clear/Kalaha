#pragma once

#include "AI/AbstractLayer.h"
#include "Tools/Serializable.h"

#include <memory>
#include <optional>

class Ai : public Serializable
{
public:
    explicit Ai() = default;
    Ai(const Ai &o);
    Ai &operator=(const Ai &o);

    void fromJson(const nlohmann::json &j) override;
    [[nodiscard]] nlohmann::json toJson() const override;

    [[nodiscard]] int outputSize() const;
    [[nodiscard]] const AbstractLayer &lastLayer() const;

    void addLayer(AbstractLayer *layer);
    void addLayer(std::unique_ptr<AbstractLayer> &layer);
    [[nodiscard]] std::vector<float> calculate(const std::vector<float> &input) const;
    void mutate(float stddev);

private:
    std::vector<std::unique_ptr<AbstractLayer>> m_layers;
};

