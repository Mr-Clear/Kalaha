#include "Ai.h"

#include "AI/FullyConnectedLayer.h"

#include <random>
#include <stdexcept>

Ai::Ai(const InputLayer &inputLayer) :
    m_inputLayer(inputLayer)
{ }

Ai::Ai(const Ai &o) :
    m_inputLayer{o.m_inputLayer}
{
    m_innerLayers.reserve(o.m_innerLayers.size());
    for (const auto &i : o.m_innerLayers)
        m_innerLayers.emplace_back(std::unique_ptr<InnerLayer>(i->clone()));
}

Ai &Ai::operator=(const Ai &o)
{
    m_inputLayer = o.m_inputLayer;
    m_innerLayers.clear();
    m_innerLayers.reserve(o.m_innerLayers.size());
    for (const auto &i : o.m_innerLayers)
        m_innerLayers.emplace_back(std::unique_ptr<InnerLayer>(i->clone()));
    return *this;
}

InputLayer &Ai::inputLayer()
{
    return m_inputLayer;
}

const InputLayer &Ai::inputLayer() const
{
    return m_inputLayer;
}

int Ai::outputSize() const
{
    return lastLayer().outputSize();
}

const AbstractLayer &Ai::lastLayer() const
{
    if (m_innerLayers.empty())
        return m_inputLayer;
    return *m_innerLayers.back();
}

void Ai::addLayer(InnerLayer *layer)
{
    std::unique_ptr<InnerLayer> p{layer};
    addLayer(p);
}

void Ai::addLayer(std::unique_ptr<InnerLayer> &layer)
{
    if (layer->inputSize() != lastLayer().outputSize())
        throw std::invalid_argument{"Given layer has differnet parent than expected."};
    m_innerLayers.emplace_back(std::move(layer));
}

std::vector<float> Ai::calculate()
{
    std::vector<float> values = m_inputLayer.values();
    for (auto &l : m_innerLayers)
        values = l->calculate(values);
    return values;
}

void Ai::mutate(float stddev)
{
    std::random_device rd{};
    std::mt19937 gen{rd()};
    for (auto &l : m_innerLayers)
    {
        auto *fc = dynamic_cast<FullyConnectedLayer*>(l.get());
        if (fc)
        {
            fc->manipulateAll([stddev, &gen] (float v) {

                std::normal_distribution<> d{v, stddev};
                return d(gen);
            });
        }
    }
}
