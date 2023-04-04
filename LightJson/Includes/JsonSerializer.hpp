#pragma once

#include <string>

class JsonObject;
class JsonElement;

class JsonSerializer {
public:
    static std::string toJson(const JsonObject* jsonObject);

protected:
    static std::string parseElement(const JsonElement* jsonElement);
};
