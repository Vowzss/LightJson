#pragma once

#include "JsonType.hpp"

#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

#include "JsonValue.h"

class JsonElement : public JsonValue {
private:
    JsonType  type;
    JsonValue value;

public:
    JsonElement()                                                   : type(JsonType::Null)                              {}
    JsonElement(std::nullptr_t)                                     : type(JsonType::Null)                              {}
    JsonElement(std::string value)                                  : type(JsonType::String) , string(std::move(value)) {}
    JsonElement(const double& value)                                : type(JsonType::Number) , number(value)            {}
    JsonElement(const bool& value)                                  : type(JsonType::Boolean), boolean(value)           {}
    JsonElement(std::vector<JsonElement> value)                     : type(JsonType::Array)  , array(std::move(value))  {}
    JsonElement(std::unordered_map<std::string, JsonElement> value) : type(JsonType::Object) , object(std::move(value)) {}

public:
    JsonType getType() const {
        return type;
    }

    std::string getAsString() const {
        if (type == JsonType::String) {
            return string;
        }
        throw std::runtime_error("JSON value is not a string");
    }

    double getAsNumber() const  {
        if (type == JsonType::Number) {
            return number;
        }
        throw std::runtime_error("JSON value is not a number");
    }

    bool getAsBoolean() const  {
        if (type == JsonType::Boolean) {
            return boolean;
        }
        throw std::runtime_error("JSON value is not a boolean");
    }

    std::vector<JsonElement> getAsArray() const  {
        if (type == JsonType::Array) {
            return array;
        }
        throw std::runtime_error("JSON value is not an array");
    }

    std::unordered_map<std::string, JsonElement> getAsObject() const {
        if (type == JsonType::Object) {
            return object;
        }
        throw std::runtime_error("JSON value is not an object");
    }

    bool isNull() const {
        return type == JsonType::Null;
    }

    bool isString() const {
        return type == JsonType::String;
    }

    bool isNumber() const {
        return type == JsonType::Number;
    }

    bool isBool() const {
        return type == JsonType::Boolean;
    }

    bool isArray() const {
        return type == JsonType::Array;
    }

    bool isObject() const {
        return type == JsonType::Object;
    }

    bool hasKey(const std::string& key) const {
        if (isObject()) {
            return object.count(key) > 0;
        }
        throw std::runtime_error("JSON value is not an object");
    }

    JsonElement operator[](const int& index) const {
        if (isArray()) {
            return array.at(index);
        }
        throw std::runtime_error("JSON value is not an array");
    }

    JsonElement operator[](const std::string& key) const {
        if (isObject() && object.count(key) > 0) {
            return object.at(key);
        }
        throw std::runtime_error("Key not found in object: " + key);
    }
};
