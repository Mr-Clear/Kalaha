#include "Ai.h"

#include "AI/FullyConnectedLayer.h"

#include <random>
#include <stdexcept>

using nlohmann::json;

Ai::Ai(const Ai &o)
{
    m_layers.reserve(o.m_layers.size());
    for (const auto &i : o.m_layers)
        m_layers.emplace_back(std::unique_ptr<AbstractLayer>(i->clone()));
}

Ai &Ai::operator=(const Ai &o)
{
    m_layers.clear();
    m_layers.reserve(o.m_layers.size());
    for (const auto &i : o.m_layers)
        m_layers.emplace_back(std::unique_ptr<AbstractLayer>(i->clone()));
    return *this;
}

void Ai::fromJson(const json &j)
{
    if (j.empty())
        throw std::invalid_argument("JSON for Ai is empty!");
    if (!j.contains("layers"))
        throw std::invalid_argument("JSON for Ai has no layers defined!");

    m_layers.clear();
    for (const auto &[_, layer]  : j["layers"].items())
    {
        m_layers.emplace_back(AbstractLayer::layerFromJson(layer));
    }
}

json Ai::toJson() const
{
    nlohmann::json j{{"layers", json::array()}};
    for (const auto &l : m_layers)
    {
        j["layers"].emplace_back(l->toJson());
    }
    return j;
}

int Ai::outputSize() const
{
    for (auto l = m_layers.rbegin(); l != m_layers.rend(); ++l)
    {
        if ((*l)->outputSize() != -1)
            return (*l)->outputSize();
    }
    return -1;
}

const AbstractLayer &Ai::lastLayer() const
{
    return {*m_layers.back()};
}

void Ai::addLayer(AbstractLayer *layer)
{
    std::unique_ptr<AbstractLayer> p{layer};
    addLayer(p);
}

void Ai::addLayer(std::unique_ptr<AbstractLayer> &layer)
{
    if (outputSize() != layer->inputSize() && outputSize() != -1 && layer->inputSize() != -1)
        throw std::invalid_argument{"Given layer different input size (" + std::to_string(layer->inputSize()) + ") "
                                    "than previous layers output size (" + std::to_string(lastLayer().outputSize()) + ")."};
    m_layers.emplace_back(std::move(layer));
}

std::vector<float> Ai::calculate(const std::vector<float> &input) const
{
    if (m_layers.size() && input.size() != m_layers.front()->inputSize())
        throw std::invalid_argument{"Input has different size (" + std::to_string(input.size()) + ") "
                                    "than first layer input size (" + std::to_string(m_layers.front()->inputSize()) + ")."};
    std::vector<float> values = input;
    for (auto &l : m_layers)
        values = l->calculate(values);
    return values;
}

void Ai::mutate(float stddev)
{
    std::random_device rd{};
    std::mt19937 gen{rd()};
    for (auto &l : m_layers)
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
