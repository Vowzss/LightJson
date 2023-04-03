#pragma once

#include "JsonElement.hpp"
#include "../Includes/JsonDeserializer.hpp"
#include "../Includes/JsonSerializer.hpp"

#include <string>
#include <stdexcept>

class JsonObject {
private:
    JsonElement element;

public:
    JsonObject() = default;

    JsonObject(const std::string& json) {
        element = JsonDeserializer::fromJson(json);
    }

    JsonObject(const JsonElement& element) : element(element) {}

    JsonElement getElement() const {
        return element;
    }

    JsonElement getElement(const std::string& key) const {
        if (element.isObject() && element.hasKey(key)) {
            return element.getAsObject().at(key);
        }
        throw std::runtime_error("Key not found in object: " + key);
    }


    void setElement(const std::string& key, const JsonElement& element) const {
        if (element.isObject()) {
            element.getAsObject()[key] = element;
        }
        else {
            throw std::runtime_error("Cannot set value in non-object JSON");
        }
    }

    std::string toJson() const {
        return JsonSerializer::toJson(element);
    }
};