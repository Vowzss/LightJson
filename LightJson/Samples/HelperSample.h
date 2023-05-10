#pragma once
#include <string>

#include "../Includes/JsonVirtual.h"
#include "../Includes/JsonElement.h"

class AnObject
{
public:
    double aDoubleValue = 2.35151846165651;
};

class AnotherObject : public LightJson::JsonVirtual
{
public:
    std::string aStringValue = "AString";
    int aIntValue = 152881;
    float aFloatValue = 0.5151515f;

    LightJson::JsonElement* Serialize() const                   override;
    void Deserialize(const LightJson::JsonElement* jsonElement) override;
};

class TrickyObject
{
public:
    long aLongValue = 56111L;
    AnObject aObject{};
    AnotherObject aOtherObject{};
};

