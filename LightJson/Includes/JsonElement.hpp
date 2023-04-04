#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

enum class JsonType;

class JsonElement {
protected:
    JsonUtils::JsonType type;
    
public:
    JsonElement() : type(JsonUtils::JsonType::Null) {}
    virtual ~JsonElement() = default;
    
    virtual std::string                                           getAsString()  const { throw std::runtime_error("Element is not a string");  }
    virtual double                                                getAsNumber()  const { throw std::runtime_error("Element is not a number");  }
    virtual bool                                                  getAsBoolean() const { throw std::runtime_error("Element is not a boolean"); }
    virtual const  std::vector<JsonElement*> &                    getAsArray()   const { throw std::runtime_error("Element is not an array");  }
    virtual const  std::unordered_map<std::string, JsonElement*>& getAsObject()  const { throw std::runtime_error("Element is not an object"); }
    
    bool isOfType(const JsonUtils::JsonType& _type) const { return type == _type; }

    JsonUtils::JsonType getType() const { return type; }
};


class StringElement : public JsonElement {
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


class NumberElement : public JsonElement {
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


class BooleanElement : public JsonElement {
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


class ArrayObject : public JsonElement {
private:
    std::vector<JsonElement*> value;
    
public:
    explicit ArrayObject(std::vector<JsonElement*> value);
    const std::vector<JsonElement*>& getAsArray() const override { return value; }
};
inline ArrayObject::ArrayObject(std::vector<JsonElement*> value) : value(std::move(value))
{
    type = JsonUtils::JsonType::Array;
}


class ObjectElement : public JsonElement {
private:
    std::unordered_map<std::string, JsonElement*> value;
    
public:
    explicit ObjectElement(std::unordered_map<std::string, JsonElement*> value);
    const std::unordered_map<std::string, JsonElement*>& getAsObject() const override { return value; }
};
inline ObjectElement::ObjectElement(std::unordered_map<std::string, JsonElement*> value) : value(std::move(value))
{
    type = JsonUtils::JsonType::Object;
}
