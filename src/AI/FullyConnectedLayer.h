#pragma once

#include "AI/AbstractLayer.h"

#include <functional>
#include <iostream>
#include <vector>

class FullyConnectedLayer : public AbstractLayer
{
public:
    FullyConnectedLayer(int inputSize, int outputSize);
    FullyConnectedLayer(const nlohmann::json &json);
    [[nodiscard]] FullyConnectedLayer *clone() const override;

    [[nodiscard]] int inputSize() const override;
    [[nodiscard]] int outputSize() const override;
    std::vector<float> calculate(const std::vector<float> &input) override;

    [[nodiscard]] float gain(int myId, int preId) const;
    [[nodiscard]] float bias(int id) const;

    void setGain(int myId, int preId, float gain);
    void setGains(const std::initializer_list<std::initializer_list<float>> &gainValues);
    void setGains(int myId, const std::initializer_list<float> &gainValues);
    void setBiases(const std::initializer_list<float> &biasValues);
    void setBiases(int id, float bias);

    void manipulateGain(const std::function<float(float)> &fn);
    void manipulateBias(const std::function<float(float)> &fn);
    void manipulateAll(const std::function<float(float)> &fn);

    void fromJson(const nlohmann::json &j) override;
    [[nodiscard]] nlohmann::json toJson() const override;

private:
    std::vector<std::vector<float>> m_gains;
    std::vector<float> m_biases;
};
