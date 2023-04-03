#pragma once

#include "JsonElement.hpp"
#include "../Includes/JsonDeserializer.hpp"
#include "../Includes/JsonSerializer.hpp"

#include <string>
#include <stdexcept>

class JsonObject
{
private:
    std::unordered_map<std::string, JsonElement*> elements;

public:
    JsonObject() = default;

    JsonObject(const std::string& json) {
        elements = JsonDeserializer::fromJson(json);
    }

    JsonObject(std::unordered_map<std::string, JsonElement*> elements) : elements(std::move(elements)) {}
    
    std::unordered_map<std::string, JsonElement*> getMembers() const {
        return elements;
    }

    JsonElement* getMember(const std::string& key) {
        if(!hasKey(key)) {
            throw std::runtime_error("Key not found in object: " + key);
        }
        return elements[key];
    }


    void setMember(const std::string& key, JsonElement* element) {
        elements[key] = element;
    }

    bool hasKey(const std::string& _key) const {
        return elements.count(_key) > 0;
    }
};