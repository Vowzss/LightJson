#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

#include "JsonType.hpp"

enum class JsonType;

class JsonElement {
protected:
    std::string key;
    JsonType    type;
    
public:
    JsonElement(std::string _key) : key(std::move(_key)), type(JsonType::Null) {}
    virtual ~JsonElement() = default;
    
    virtual std::string                                           getAsString()  const { throw std::runtime_error("Element is not a string");  }
    virtual double                                                getAsNumber()  const { throw std::runtime_error("Element is not a number");  }
    virtual bool                                                  getAsBoolean() const { throw std::runtime_error("Element is not a boolean"); }
    virtual const  std::vector<JsonElement*>&                     getAsArray()   const { throw std::runtime_error("Element is not an array");  }
    virtual const  std::unordered_map<std::string, JsonElement*>& getAsObject()  const { throw std::runtime_error("Element is not an object"); }
    
    bool isOfType(const JsonType& _type) const { return type == _type; }

    JsonType    getType() const { return type; }
    std::string getKey()  const { return key;  }
};


class StringElement : public JsonElement {
private:
    std::string value;
    
public:
    explicit StringElement(std::string _key, std::string value);
    std::string getAsString() const override { return value; }
};
inline StringElement::StringElement(std::string _key, std::string value): JsonElement(std::move(_key)), value(std::move(value))
{
    type = JsonType::String;
}


class NumberElement : public JsonElement {
private:
    double value;
    
public:
    explicit NumberElement(std::string _key, const double& value);
    double getAsNumber() const override { return value; }
};
inline NumberElement::NumberElement(std::string _key, const double& value): JsonElement(std::move(_key)), value(value)
{
    type = JsonType::Number;
}


class BooleanElement : public JsonElement {
private:
    bool value;
    
public:
    explicit BooleanElement(std::string _key, const bool& value);
    bool getAsBoolean() const override { return value; }
};
inline BooleanElement::BooleanElement(std::string _key, const bool& value): JsonElement(std::move(_key)), value(value)
{
    type = JsonType::Boolean;
}


class ArrayObject : public JsonElement {
private:
    std::vector<JsonElement*> value;
    
public:
    explicit ArrayObject(std::string _key, std::vector<JsonElement*> value);
    const std::vector<JsonElement*>& getAsArray() const override { return value; }
};
inline ArrayObject::ArrayObject(std::string _key, std::vector<JsonElement*> value): JsonElement(std::move(_key)), value(std::move(value))
{
    type = JsonType::Array;
}


class ObjectElement : public JsonElement {
private:
    std::unordered_map<std::string, JsonElement*> value;
    
public:
    explicit ObjectElement(std::string _key, std::unordered_map<std::string, JsonElement*> value);
    const std::unordered_map<std::string, JsonElement*>& getAsObject() const override { return value; }
};
inline ObjectElement::ObjectElement(std::string _key, std::unordered_map<std::string, JsonElement*> value): JsonElement(std::move(_key)), value(std::move(value))
{
    type = JsonType::Object;
}
