#include "Ai.h"

#include "AI/FullyConnectedLayer.h"

#include <random>
#include <stdexcept>

Ai::Ai(const InputLayer &inputLayer) :
    m_inputLayer(inputLayer)
{ }

int Ai::size() const
{
    return lastLayer().size();
}

const AbstractLayer &Ai::lastLayer() const
{
    if (m_innerLayers.empty())
        return m_inputLayer;
    return m_innerLayers.back().get();
}

float Ai::operator[](int index) const
{
    return lastLayer()[index];
}

void Ai::addLayer(InnerLayer &layer)
{
    if (&layer.predecessor() != &lastLayer())
        throw std::invalid_argument{"Given layer has differnet parent than expected."};
    m_innerLayers.emplace_back(layer);
}

void Ai::calculate()
{
    for (auto &l : m_innerLayers)
        l.get().calculate();
}

void Ai::mutate(float stddev)
{
    std::random_device rd{};
    std::mt19937 gen{rd()};
    for (InnerLayer &l : m_innerLayers)
    {
        auto *fc = dynamic_cast<FullyConnectedLayer*>(&l);
        if (fc)
        {
            fc->manipulateAll([stddev, &gen] (float v) {

                std::normal_distribution<> d{v, stddev};
                return d(gen);
            });
        }
    }
}
