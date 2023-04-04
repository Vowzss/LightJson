#pragma once
#include <unordered_map>

class JsonElement;

class JsonUtils
{
public:
    typedef std::unordered_map<std::string, JsonElement*>              JsonMap;
    typedef std::make_pair    <const std::string&, const JsonElement&> JsonPair;

    enum class JsonType {
        Null,
        Boolean,
        Number,
        String,
        Array,
        Object
    };
};
