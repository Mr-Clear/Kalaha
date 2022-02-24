#include "InnerLayer.h"

InnerLayer::InnerLayer(int inputSize) :
    m_inputSize{inputSize}
{ }

int InnerLayer::inputSize() const
{
    return m_inputSize;
}
