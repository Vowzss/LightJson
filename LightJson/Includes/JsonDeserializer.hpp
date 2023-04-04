#pragma once

#include <unordered_map>

#include "JsonUtils.h"

class JsonElement;
class JsonObject;

class JsonDeserializer {
public:
    static JsonUtils::JsonMap fromJson(const std::string& json);
    
protected:
    static std::pair<const std::string&, const JsonElement&> parseString(const std::string& string);
    static JsonElement parseArray(const std::string& string);
};
