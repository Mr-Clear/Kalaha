#include <utility>

#include "AbstractLayer.h"


AbstractLayer::AbstractLayer(const std::string &name, std::function<AbstractLayer *()> constructor)
{
    registerLayer(name, std::move(constructor));
}

AbstractLayer *AbstractLayer::layerFromJson(const nlohmann::json &j)
{
    const std::string name = j.begin().key();
    AbstractLayer *layer = constructors()[name]();
    layer->fromJson(j);
    return layer;
}

void AbstractLayer::registerLayer(const std::string &name, std::function<AbstractLayer *()> constructor)
{
    constructors()[name] = std::move(constructor);
}

std::unordered_map<std::string, std::function<AbstractLayer *()> > &AbstractLayer::constructors()
{
    static std::unordered_map<std::string, std::function<AbstractLayer*()>> map;
    return map;
}
