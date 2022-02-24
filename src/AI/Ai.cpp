#include "Ai.h"

#include "AI/FullyConnectedLayer.h"

#include <random>
#include <stdexcept>

Ai::Ai(const Ai &o)
{
    m_AbstractLayers.reserve(o.m_AbstractLayers.size());
    for (const auto &i : o.m_AbstractLayers)
        m_AbstractLayers.emplace_back(std::unique_ptr<AbstractLayer>(i->clone()));
}

Ai &Ai::operator=(const Ai &o)
{
    m_AbstractLayers.clear();
    m_AbstractLayers.reserve(o.m_AbstractLayers.size());
    for (const auto &i : o.m_AbstractLayers)
        m_AbstractLayers.emplace_back(std::unique_ptr<AbstractLayer>(i->clone()));
    return *this;
}

int Ai::outputSize() const
{
    if (m_AbstractLayers.empty())
        return 0;
    return lastLayer().outputSize();
}

const AbstractLayer &Ai::lastLayer() const
{
    return {*m_AbstractLayers.back()};
}

void Ai::addLayer(AbstractLayer *layer)
{
    std::unique_ptr<AbstractLayer> p{layer};
    addLayer(p);
}

void Ai::addLayer(std::unique_ptr<AbstractLayer> &layer)
{
    if (m_AbstractLayers.size() && layer->inputSize() != lastLayer().outputSize())
        throw std::invalid_argument{"Given layer different input size (" + std::to_string(layer->inputSize()) + ") "
                                    "than previous layers output size (" + std::to_string(lastLayer().outputSize()) + ")."};
    m_AbstractLayers.emplace_back(std::move(layer));
}

std::vector<float> Ai::calculate(const std::vector<float> &input)
{
    if (m_AbstractLayers.size() && input.size() != m_AbstractLayers.front()->inputSize())
        throw std::invalid_argument{"Input has different size (" + std::to_string(input.size()) + ") "
                                    "than first layer input size (" + std::to_string(m_AbstractLayers.front()->inputSize()) + ")."};
    std::vector<float> values = input;
    for (auto &l : m_AbstractLayers)
        values = l->calculate(values);
    return values;
}

void Ai::mutate(float stddev)
{
    std::random_device rd{};
    std::mt19937 gen{rd()};
    for (auto &l : m_AbstractLayers)
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
