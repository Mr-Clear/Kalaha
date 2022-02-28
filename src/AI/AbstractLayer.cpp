#include <utility>

#include "AbstractLayer.h"

namespace {
void checkLayerTypeExisting(const nlohmann::json &j)
{
    if (!j.contains("LayerType"))
        throw std::invalid_argument("JSON for FunctionLayer does not conatin a LayerType: " + j.dump());
}
}

AbstractLayer::AbstractLayer(const std::string &name, std::function<AbstractLayer *()> constructor)
{
    registerLayer(name, std::move(constructor));
}

AbstractLayer *AbstractLayer::layerFromJson(const nlohmann::json &j)
{
    checkLayerTypeExisting(j);
    const std::string name = j["LayerType"];
    if (!constructors().contains(name) || !constructors()[name])
        throw std::invalid_argument{"AI Layer not known: " + name};
    AbstractLayer *layer = constructors()[name]();
    layer->fromJson(j);
    return layer;
}

void AbstractLayer::registerLayer(const std::string &name, std::function<AbstractLayer *()> constructor)
{
    constructors()[name] = std::move(constructor);
}

void AbstractLayer::verifyLayerType(const nlohmann::json &json, const std::string &type)
{
    checkLayerTypeExisting(json);
    if (json["LayerType"] != type)
        throw std::invalid_argument(std::string{"JSON for " + type + " specifies a different layer type: "} + json["LayerType"].dump());
}

std::unordered_map<std::string, std::function<AbstractLayer *()> > &AbstractLayer::constructors()
{
    static std::unordered_map<std::string, std::function<AbstractLayer*()>> map;
    return map;
}
