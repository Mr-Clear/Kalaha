#pragma once

#include "Tools/Serializable.h"

#include <vector>

class AbstractLayer : public Serializable
{
public:
    AbstractLayer(const std::string &name, std::function<AbstractLayer*()> constructor);
    [[nodiscard]] virtual int inputSize() const = 0;
    [[nodiscard]] virtual int outputSize() const = 0;

    virtual std::vector<float> calculate(const std::vector<float> &input) = 0;

    [[nodiscard]] virtual AbstractLayer *clone() const = 0;

    static AbstractLayer *layerFromJson(const nlohmann::json &j);

protected:
    static void registerLayer(const std::string &name, std::function<AbstractLayer*()> constructor);
    void verifyLayerType(const nlohmann::json &json, const std::string &type);

private:
    static std::unordered_map<std::string, std::function<AbstractLayer*()>> &constructors();
};

