#include "AbstractLayer.h"

AbstractLayer::AbstractLayer(int inputSize) :
    m_inputSize{inputSize}
{ }

int AbstractLayer::inputSize() const
{
    return m_inputSize;
}
