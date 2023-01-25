#pragma once

#include <string>

#include "Includes/StringUtils.h"

class JsonElement
{
public:
    JsonElement(const std::string& pValue);
    ~JsonElement();
    
    std::string getValue() const
    {
        return value;
    }

    JsonElement* GetChild() const
    {
        return child;
    }

    int getAsInt() const
    {
        return StringUtils::ToInt(value);
    }
    
    bool getAsBool() const
    {
        return StringUtils::ToBool(value);
    }

    float getAsFloat() const
    {
        return StringUtils::ToFloat(value);
    }

    double getAsDouble() const
    {
        return StringUtils::ToDouble(value);
    }
    
private:
    std::string value;
    JsonElement* child = nullptr;
};
