#pragma once

#include "JsonUtils.h"

namespace LightJson
{
    class JsonHelper
    {
    public:
        template <typename T> static JsonElement* Serialize(const T& value);
        template <typename T> static T Deserialize(JsonUtils::JsonMap jsonMap);
    };
}