#include "FunctionLayer.h"

#include <cmath>

std::unordered_map<std::string, std::function<float(float)>> FunctionLayer::s_knownFunctions;

const FunctionLayer FunctionLayer::RELU{"RELU", [] (float v)
    { return v <= 0 ? 0 : v; }};
const FunctionLayer FunctionLayer::GELU{"GELU", [] (float v)
    { return v * erfc(-v / sqrt(2)) / 2.f; }};

FunctionLayer::FunctionLayer(const std::string &name, const std::function<float(float)> &fn) :
    AbstractLayer{"FunctionLayer", [ ] { return new FunctionLayer("Identity", [] (float v) { return v; }); }},
    m_name{name},
    m_fn{fn}
{
    s_knownFunctions[name] = m_fn;
}

FunctionLayer *FunctionLayer::clone() const
{
    return new FunctionLayer(*this);
}

int FunctionLayer::inputSize() const
{
    return -1;
}

int FunctionLayer::outputSize() const
{
    return -1;
}

std::vector<float> FunctionLayer::calculate(const std::vector<float> &input)
{
    std::vector<float> output;
    output.reserve(input.size());
    for (float i : input)
            output.emplace_back(m_fn(i));
    return output;
}

void FunctionLayer::fromJson(const nlohmann::json &json)
{
    auto j = json;
    if (json.contains("FunctionLayer"))
        j = json["FunctionLayer"];
    if (!j.is_string())
        throw std::invalid_argument("JSON for FunctionLayer does not conatin a name: " + json.dump());

    std::string name = j;
    if (!s_knownFunctions.contains(name))
        throw std::invalid_argument("JSON for FunctionLayer conatins unknown name: " + name);

    m_fn = s_knownFunctions[name];
}

nlohmann::json FunctionLayer::toJson() const
{
    return {{"FunctionLayer", m_name}};
}
