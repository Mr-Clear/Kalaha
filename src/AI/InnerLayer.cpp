#include "InnerLayer.h"

InnerLayer::InnerLayer(const AbstractLayer &predecessor) :
    m_predecessor{predecessor}
{ }

const AbstractLayer &InnerLayer::predecessor() const
{
    return m_predecessor;
}
