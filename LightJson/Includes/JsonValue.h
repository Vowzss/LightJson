#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

class JsonElement;

class JsonValue {
public:
    virtual ~JsonValue() = default;
    virtual std::string asString() const = 0;
    virtual double asNumber() const = 0;
    virtual bool asBoolean() const = 0;
    virtual const std::vector<JsonElement>& asArray() const = 0;
    virtual const std::unordered_map<std::string, JsonElement>& asObject() const = 0;
};

class JsonString : public JsonValue {
private:
    std::string value;
    
public:
    explicit JsonString(std::string value) : value(std::move(value)) {}
    
    std::string asString()                                         const override { return value; }
    double asNumber()                                              const override { throw std::runtime_error("Not a number"); }
    bool   asBoolean()                                             const override { throw std::runtime_error("Not a boolean"); }
    const std::vector<JsonElement>& asArray()                      const override { throw std::runtime_error("Not an array"); }
    const std::unordered_map<std::string, JsonElement>& asObject() const override { throw std::runtime_error("Not an object"); }
};

class JsonNumber : public JsonValue {
private:
    double value;
    
public:
    explicit JsonNumber(const double& value) : value(value) {}
    
    double asNumber()                                              const override { return value; }
    std::string asString()                                         const override { throw std::runtime_error("Not a string"); }
    bool asBoolean()                                               const override { throw std::runtime_error("Not a boolean"); }
    const std::vector<JsonElement>& asArray()                      const override { throw std::runtime_error("Not an array"); }
    const std::unordered_map<std::string, JsonElement>& asObject() const override { throw std::runtime_error("Not an object"); }
};

class JsonBoolean : public JsonValue {
private:
    bool value;
    
public:
    explicit JsonBoolean(const bool& value) : value(value) {}
    
    bool asBoolean()                                               const override { return value; }
    std::string asString()                                         const override { throw std::runtime_error("Not a string"); }
    double asNumber()                                              const override { throw std::runtime_error("Not a number"); }
    const std::vector<JsonElement>& asArray()                      const override { throw std::runtime_error("Not an array"); }
    const std::unordered_map<std::string, JsonElement>& asObject() const override { throw std::runtime_error("Not an object"); }
};

class JsonArray : public JsonValue {
private:
    std::vector<JsonElement> value;
    
public:
    explicit JsonArray(std::vector<JsonElement> value) : value(std::move(value)) {}
    
    const std::vector<JsonElement>& asArray()                      const override { return value; }
    std::string asString()                                         const override { throw std::runtime_error("Not a string"); }
    double asNumber()                                              const override { throw std::runtime_error("Not a number"); }
    bool asBoolean()                                               const override { throw std::runtime_error("Not a boolean"); }
    const std::unordered_map<std::string, JsonElement>& asObject() const override { throw std::runtime_error("Not an object"); }
};
