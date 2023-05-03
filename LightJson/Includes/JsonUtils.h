#pragma once

#include <unordered_map>

namespace LightJson
{
    class JsonElement;
    class JsonObject;
    
    enum class JsonType {
        Null,
        Boolean,
        Float,
        Double,
        Long,
        Short,
        Char,
        Integer,
        String,
        Array,
        Object
    };

    class JsonUtils
    {
    public:
        typedef std::unordered_map<std::string, JsonElement*> JsonMap;
        typedef std::vector<JsonElement*>                     JsonArray;
        typedef std::pair<std::string, JsonElement*>          JsonPair;

        static JsonPair makeJsonPair(std::string key, JsonElement* element)
        {
            return std::make_pair<std::string, JsonElement*>(std::move(key), std::move(element));
        }
    };
}
