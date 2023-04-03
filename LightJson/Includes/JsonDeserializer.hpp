#pragma once
#include "JsonElement.hpp"

class JsonDeserializer {
public:
    static JsonElement fromJson(const std::string& json);
};
