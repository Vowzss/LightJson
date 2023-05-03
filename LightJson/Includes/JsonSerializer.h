#pragma once

#include <string>

namespace LightJson
{
    class JsonObject;
    class JsonElement;

    class JsonSerializer {
    public:
        static std::string toJson(const JsonObject* jsonObject);
        static void toFile(const JsonObject* jsonObject, const std::string& filename);

    protected:
        static std::string parseElement(const JsonElement* jsonElement);
    };
}
