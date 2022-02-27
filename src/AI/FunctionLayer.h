#pragma once

#include "AI/AbstractLayer.h"

#include <functional>
#include <unordered_map>

class FunctionLayer : public AbstractLayer
{
public:
    FunctionLayer(const std::string &name, const std::function<float(float)> &fn);

    [[nodiscard]] FunctionLayer *clone() const override;

    [[nodiscard]] int inputSize() const override;
    [[nodiscard]] int outputSize() const override;
    std::vector<float> calculate(const std::vector<float> &input) override;

    void fromJson(const nlohmann::json &json) override;
    [[nodiscard]] nlohmann::json toJson() const override;

    static const FunctionLayer RELU;
    static const FunctionLayer GELU;

private:
    std::string m_name;
    std::function<float(float)> m_fn;

    static std::unordered_map<std::string, std::function<float(float)>> s_knownFunctions;
};
