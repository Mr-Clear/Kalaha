#include "FullyConnectedLayer.h"

#include <cassert>

FullyConnectedLayer::FullyConnectedLayer(int inputSize, int outputSize) :
    AbstractLayer{"FullyConnectedLayer", [ ] { return new FullyConnectedLayer(0, 0); }},
    m_gains(outputSize, std::vector<float>(inputSize, 1.f / inputSize)),
    m_biases(outputSize, 0)
{ }

FullyConnectedLayer::FullyConnectedLayer(const nlohmann::json &json) :
    FullyConnectedLayer{0, 0}
{
    fromJson(json);
}

FullyConnectedLayer *FullyConnectedLayer::clone() const
{
    return new FullyConnectedLayer(*this);
}

int FullyConnectedLayer::inputSize() const
{
    if (m_gains.empty())
        return 0;
    return m_gains.front().size();
}

int FullyConnectedLayer::outputSize() const
{
    return m_biases.size();
}

std::vector<float> FullyConnectedLayer::calculate(const std::vector<float> &input)
{
    std::vector<float> output;
    output.reserve(outputSize());
    for (int i = 0; i < outputSize(); ++i)
    {
        const auto &g = m_gains.at(i);
        float val = m_biases.at(i);
        for (int j = 0; j < input.size(); ++j)
        {
            val += input[j] * g.at(j);
        }
        output.emplace_back(val);
    }
    return output;
}

float FullyConnectedLayer::gain(int myId, int preId) const
{
    return m_gains.at(myId).at(preId);
}

float FullyConnectedLayer::bias(int id) const
{
    return m_biases.at(id);
}

void FullyConnectedLayer::setGain(int myId, int preId, float gain)
{
    m_gains.at(myId).at(preId) = gain;
}

void FullyConnectedLayer::setGains(const std::initializer_list<std::initializer_list<float>> &gainValues)
{
    if (gainValues.size() != outputSize())
        throw std::length_error{"Gain values size must be " + std::to_string(outputSize()) + " but is " + std::to_string(gainValues.size()) + "."};
    auto ig = m_gains.begin();
    auto iv = gainValues.begin();
    for (; ig != m_gains.end(); ++ig, ++iv)
    {
        if (iv->size() != inputSize())
            throw std::length_error{"Gain values size must be " + std::to_string(inputSize()) + " but is " + std::to_string(iv->size()) + "."};
        assert(iv != gainValues.end());
        *ig = *iv;
    }
}

void FullyConnectedLayer::setGains(int id, const std::initializer_list<float> &gainValues)
{
    if (gainValues.size() != inputSize())
        throw std::length_error{"Gain values size must be " + std::to_string(outputSize()) + " but is " + std::to_string(gainValues.size()) + "."};
    m_gains.at(id) = gainValues;
}

void FullyConnectedLayer::setBiases(const std::initializer_list<float> &biasValues)
{
    if (biasValues.size() != outputSize())
        throw std::length_error{"Bias values size must be " + std::to_string(outputSize()) + " but is " + std::to_string(biasValues.size()) + "."};
    m_biases = biasValues;
}

void FullyConnectedLayer::setBiases(int id, float bias)
{
    m_biases.at(id) = bias;
}

void FullyConnectedLayer::manipulateGain(const std::function<float (float)> &fn)
{
    for (int i = 0; i < outputSize(); ++i)
    {
        auto &g = m_gains.at(i);
        for (int j = 0; j < inputSize(); ++j)
        {
            g.at(j) = fn(g.at(j));
        }
    }
}

void FullyConnectedLayer::manipulateBias(const std::function<float (float)> &fn)
{
    for (float &b : m_biases)
        b = fn(b);
}

void FullyConnectedLayer::manipulateAll(const std::function<float (float)> &fn)
{
    manipulateGain(fn);
    manipulateBias(fn);
}

void FullyConnectedLayer::fromJson(const nlohmann::json &json)
{
    m_gains.clear();
    m_biases.clear();

    verifyLayerType(json, "FullyConnectedLayer");

    std::vector<std::vector<float>> gains;
    std::vector<float> biases;
    if (json.empty())
        return;

    for (const std::string &k : {std::string{"gains"}, {"biases"}})
    {
        if (!json.contains(k))
            throw std::invalid_argument("JSON for FullyConnectedLayer misses " + k + "!");
        if (json[k].empty())
            throw std::invalid_argument("JSON for FullyConnectedLayer contains no " + k + "!");
        if (!json[k].is_array())
            throw std::invalid_argument("JSON for FullyConnectedLayer value " + k + " in no array!");
    }

    if (json["gains"].size() != json["biases"].size())
        throw std::invalid_argument("JSON for FullyConnectedLayer gains and biases have different sizes!");

    int outSize = -1;
    for (const nlohmann::json &neuronGains : json["gains"])
    {
        if (neuronGains.size() == 0)
            throw std::invalid_argument("JSON for FullyConnectedLayer gains are empty!");
        if (outSize == -1)
            outSize = neuronGains.size();
        else
            if (neuronGains.size() != outSize)
                throw std::invalid_argument("JSON for FullyConnectedLayer gains have varying size!");
        std::vector<float> g;
        for (const nlohmann::json &v : neuronGains)
        {
            if (!v.is_number())
                throw std::invalid_argument("JSON for FullyConnectedLayer contains non numeric gain!");
            g.emplace_back(v);
        }
        gains.push_back(g);
    }
    for (const nlohmann::json &v : json["biases"])
    {
        if (!v.is_number())
            throw std::invalid_argument("JSON for FullyConnectedLayer contains non numeric bias!");
        biases.push_back(v);
    }

    m_gains = gains;
    m_biases = biases;
}

nlohmann::json FullyConnectedLayer::toJson() const
{
    nlohmann::json neuronGains = nlohmann::json::array();
    for (const auto &g : m_gains)
    {
        auto gains = nlohmann::json::array();
        for (float v : g)
            gains.push_back(v);
        neuronGains.push_back(gains);
    }
    nlohmann::json biases = nlohmann::json::array();
    for (float b : m_biases)
        biases.push_back(b);
    return {{"LayerType", "FullyConnectedLayer"}, {"gains", neuronGains}, {"biases", biases}};
}
