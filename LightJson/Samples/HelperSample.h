#pragma once
#include <string>

#include "../Includes/JsonVirtual.h"
#include "../Includes/JsonElement.h"

class AnObject
{
public:
    double aDoubleValue;
};

class AnotherObject : public LightJson::JsonVirtual
{
public:
    std::string aStringValue;
    int aIntValue;
    float aFloatValue;

    LightJson::JsonElement* Serialize()                 const override;
    void Serialize(LightJson::JsonObject& jsonObject)   const override;  
    void Deserialize(LightJson::JsonObject& jsonObject) override;
};

class TrickyObject
{
public:
    long aLongValue;
    AnObject aObject;
    AnotherObject aOtherObject;
};

