#pragma once
#include "JsonElement.hpp"

class JsonDeserializer {
public:
    static std::unordered_map<std::string, JsonElement*> fromJson(const std::string& json);
};
