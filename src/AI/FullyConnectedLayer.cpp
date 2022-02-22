#include "FullyConnectedLayer.h"

#include <cassert>

FullyConnectedLayer::FullyConnectedLayer(int size, const AbstractLayer &predecessor) :
    InnerLayer{predecessor},
    m_gains(size, std::vector<float>(predecessor.size(), 1.f / predecessor.size())),
    m_bias(size, 0),
    m_values(size, 0)
{ }

int FullyConnectedLayer::size() const
{
    return m_bias.size();
}

float FullyConnectedLayer::operator[](int index) const
{
    return m_values.at(index);
}

void FullyConnectedLayer::calculate()
{
    for (int i = 0; i < size(); ++i)
    {
        const auto &g = m_gains.at(i);
        float val = m_bias.at(i);
        for (int j = 0; j < predecessor().size(); ++j)
        {
            val += predecessor()[j] * g.at(j);
        }
        m_values.at(i) = val;
    }
}

float FullyConnectedLayer::gain(int myId, int preId) const
{
    return m_gains.at(myId).at(preId);
}

float FullyConnectedLayer::bias(int id) const
{
    return m_bias.at(id);
}

void FullyConnectedLayer::setGain(int myId, int preId, float gain)
{
    m_gains.at(myId).at(preId) = gain;
}

void FullyConnectedLayer::setGains(const std::initializer_list<std::initializer_list<float>> &gainValues)
{
    if (gainValues.size() != size())
        throw std::length_error{"Gain values size must be " + std::to_string(size()) + " but is " + std::to_string(gainValues.size()) + "."};
    auto ig = m_gains.begin();
    auto iv = gainValues.begin();
    for (; ig != m_gains.end(); ++ig, ++iv)
    {
        if (iv->size() != predecessor().size())
            throw std::length_error{"Gain values size must be " + std::to_string(predecessor().size()) + " but is " + std::to_string(iv->size()) + "."};
        assert(iv != gainValues.end());
        *ig = *iv;
    }
}

void FullyConnectedLayer::setGains(int id, const std::initializer_list<float> &gainValues)
{
    if (gainValues.size() != predecessor().size())
        throw std::length_error{"Gain values size must be " + std::to_string(size()) + " but is " + std::to_string(gainValues.size()) + "."};
    m_gains.at(id) = gainValues;
}

void FullyConnectedLayer::setBias(const std::initializer_list<float> &biasValues)
{
    if (biasValues.size() != size())
        throw std::length_error{"Bias values size must be " + std::to_string(size()) + " but is " + std::to_string(biasValues.size()) + "."};
    m_bias = biasValues;
}

void FullyConnectedLayer::setBias(int id, float bias)
{
    m_bias.at(id) = bias;
}

void FullyConnectedLayer::manipulateGain(const std::function<float (float)> &fn)
{
    for (int i = 0; i < size(); ++i)
    {
        auto &g = m_gains.at(i);
        for (int j = 0; j < predecessor().size(); ++j)
        {
            g.at(j) = fn(g.at(j));
        }
    }
}

void FullyConnectedLayer::manipulateBias(const std::function<float (float)> &fn)
{
    for (float &b : m_bias)
        b = fn(b);

}

void FullyConnectedLayer::manipulateAll(const std::function<float (float)> &fn)
{
    manipulateGain(fn);
    manipulateBias(fn);
}

std::string FullyConnectedLayer::toJson() const
{
    std::string s("{\"gains\":[");
    for (const auto &g : m_gains)
    {
        s += "[";
        for (float v : g)
            s += std::to_string(v) + ",";
        s += "],";
    }
    s += "],biases[";
    for (float b : m_bias)
        s += std::to_string(b) + ",";
    s += "]}";
    return s;
}
