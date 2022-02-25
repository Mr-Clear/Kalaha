#include "Serializable.h"

void Serializable::save(const std::string &filePath, const int indent) const
{
    std::ofstream out(filePath);
    out << toJson().dump(indent);
    out.close();
}
