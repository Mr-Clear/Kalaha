#pragma once

#include "AI/InnerLayer.h"

#include <functional>
#include <iostream>
#include <vector>

class FullyConnectedLayer : public InnerLayer
{
public:
    FullyConnectedLayer(int size, const AbstractLayer &predecessor);
    [[nodiscard]] int size() const override;
    [[nodiscard]] float operator[](int index) const override;
    void calculate() override;

    [[nodiscard]] float gain(int myId, int preId) const;
    [[nodiscard]] float bias(int id) const;

    void setGain(int myId, int preId, float gain);
    void setGains(const std::initializer_list<std::initializer_list<float>> &gainValues);
    void setGains(int myId, const std::initializer_list<float> &gainValues);
    void setBias(const std::initializer_list<float> &biasValues);
    void setBias(int id, float bias);

    void manipulateGain(const std::function<float(float)> &fn);
    void manipulateBias(const std::function<float(float)> &fn);
    void manipulateAll(const std::function<float(float)> &fn);

    [[nodiscard]] std::string toJson() const;

private:
    std::vector<std::vector<float>> m_gains;
    std::vector<float> m_bias;

    std::vector<float> m_values;
};
