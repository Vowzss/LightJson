#pragma once

#include "JsonUtils.h"

namespace LightJson
{
    template<typename T>
    class JsonHelper
    {
    public:
        static JsonElement* Serialize(const T& value);
        static T Deserialize(const LightJson::JsonElement* jsonElement);
    };
}