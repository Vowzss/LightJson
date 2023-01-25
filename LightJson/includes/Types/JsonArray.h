#pragma once
#include <map>
#include <string>

#include "JsonElement.h"

class JsonArray
{
public:
    JsonArray(const std::string& pKey);
    
    void AddValue(const JsonElement& pValue);

    std::string getKey() const
    {
        return key;
    }
    
private:
    std::string key;
    std::map<int, JsonElement> map;
};
