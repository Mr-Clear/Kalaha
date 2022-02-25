#pragma once

#include <nlohmann/json.hpp>

#include <fstream>

class Serializable
{
public:
    Serializable() = default;
    virtual ~Serializable() = default;
    virtual void fromJson(const nlohmann::json &j) = 0;
    [[nodiscard]] virtual nlohmann::json toJson() const = 0;

    bool operator==(const Serializable &o) const = default;

    void save(const std::string &filePath, const int indent = -1) const;
    template <class T>
    static T load(const std::string &filePath)
    {
        nlohmann::json j;
        std::ifstream i(filePath);
        i >> j;
        T t;
        t.fromJson(j);
        return t;
    }
};

