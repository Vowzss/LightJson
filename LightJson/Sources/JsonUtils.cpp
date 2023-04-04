﻿#include "../Includes/JsonUtils.h"

#include "../Includes/JsonElement.hpp"

JsonUtils::JsonPair JsonUtils::makeJsonPair(std::string key, JsonElement* element) {
    return std::make_pair<std::string, JsonElement*>(std::move(key), std::move(element));
}