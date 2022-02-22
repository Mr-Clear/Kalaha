#pragma once

#include <AI/AbstractLayer.h>

class InnerLayer : public AbstractLayer
{
public:
    InnerLayer(const AbstractLayer &predecessor);
    virtual void calculate() = 0;

    [[nodiscard]] const AbstractLayer &predecessor() const;

private:
    const AbstractLayer &m_predecessor;
};
