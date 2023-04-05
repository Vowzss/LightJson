#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <stdexcept>

#include "JsonUtils.h"

namespace LightJson
{
    class JsonElement
    {
    protected:
        JsonUtils::JsonType type;
    
    public:
        JsonElement() : type(JsonUtils::JsonType::Null) {}
        virtual ~JsonElement() = default;
    
        virtual std::string          getAsString()  const { throw std::runtime_error("Element is not a string");  }
        virtual double               getAsNumber()  const { throw std::runtime_error("Element is not a number");  }
        virtual bool                 getAsBoolean() const { throw std::runtime_error("Element is not a boolean"); }
        virtual JsonUtils::JsonArray getAsArray()   const { throw std::runtime_error("Element is not an array");  }
        virtual JsonUtils::JsonMap   getAsObject()  const { throw std::runtime_error("Element is not an object"); }
    
        bool isOfType(const JsonUtils::JsonType& _type) const { return type == _type; }

        JsonUtils::JsonType getType() const { return type; }
    };


    class StringElement final : public JsonElement
    {
    private:
        std::string value;
    
    public:
        explicit StringElement(std::string value);
        std::string getAsString() const override { return value; }
    };
    inline StringElement::StringElement(std::string value) : value(std::move(value))
    {
        type = JsonUtils::JsonType::String;
    }


    class NumberElement final : public JsonElement
    {
    private:
        double value;
    
    public:
        explicit NumberElement(const double& value);
        double getAsNumber() const override { return value; }
    };
    inline NumberElement::NumberElement(const double& value) : value(value)
    {
        type = JsonUtils::JsonType::Number;
    }


    class BooleanElement final : public JsonElement
    {
    private:
        bool value;
    
    public:
        explicit BooleanElement(const bool& value);
        bool getAsBoolean() const override { return value; }
    };
    inline BooleanElement::BooleanElement(const bool& value) : value(value)
    {
        type = JsonUtils::JsonType::Boolean;
    }


    class ArrayElement final : public JsonElement
    {
    private:
        JsonUtils::JsonArray array;
    
    public:
        explicit ArrayElement(JsonUtils::JsonArray array);
        ~ArrayElement() override {
            for(const auto* it : array) {
                delete it;
            }
            array.clear();
        }
    
        JsonUtils::JsonArray getAsArray() const override { return array; }
    };
    inline ArrayElement::ArrayElement(JsonUtils::JsonArray array) : array(std::move(array))
    {
        type = JsonUtils::JsonType::Array;
    }


    class ObjectElement final : public JsonElement
    {
    private:
        JsonUtils::JsonMap map;
    
    public:
        explicit ObjectElement(JsonUtils::JsonMap map);
        ~ObjectElement() override {
            for(const auto& it : map) {
                delete it.second;
            }
            map.clear();
        }
    
        JsonUtils::JsonMap getAsObject() const override { return map; }
    };
    inline ObjectElement::ObjectElement(JsonUtils::JsonMap map) : map(std::move(map))
    {
        type = JsonUtils::JsonType::Object;
    }
}