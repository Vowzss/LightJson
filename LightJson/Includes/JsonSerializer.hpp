#pragma once
#include "JsonElement.hpp"

class JsonSerializer {
public:
    static std::string toJson(const JsonElement& element);
};
