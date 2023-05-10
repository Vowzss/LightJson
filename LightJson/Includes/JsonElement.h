#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <stdexcept>
#include <typeinfo>

#include "JsonUtils.h"

namespace LightJson
{
    class JsonElement
    {
    protected:
        JsonType type;
    
    public:
        JsonElement() : type(JsonType::Null) {}
        virtual ~JsonElement() = default;
    
        virtual std::string          getAsString()  const { throw std::runtime_error("Element is not a string");   }
        virtual bool                 getAsBoolean() const { throw std::runtime_error("Element is not a boolean");  }
        virtual JsonUtils::JsonArray getAsArray()   const { throw std::runtime_error("Element is not an array");   }
        virtual JsonUtils::JsonMap   getAsObject()  const { throw std::runtime_error("Element is not an object");  }
        virtual float                getAsFloat()   const { throw std::runtime_error("Element is not a float");    }
        virtual int                  getAsInteger() const { throw std::runtime_error("Element is not an integer"); }
        virtual double               getAsDouble()  const { throw std::runtime_error("Element is not a double");   }
        virtual long                 getAsLong()    const { throw std::runtime_error("Element is not a long");     }
        virtual short                getAsShort()   const { throw std::runtime_error("Element is not a short");    }
        virtual char                 getAsChar()    const { throw std::runtime_error("Element is not a char");     }
    
        bool isOfType(const JsonType& _type) const { return type == _type; }

        JsonType getType() const { return type; }
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
        type = JsonType::String;
    }


    template <typename T> class NumberElement final : public JsonElement
    {
    private:
        T value;
        
    public:
        explicit NumberElement(const T& value);
        
        float  getAsFloat()   const override { return (float)value; }
        int    getAsInteger() const override { return (int)value;   }
        double getAsDouble()  const override { return (double)value; }
        long   getAsLong()    const override { return (long)value;   }
        short  getAsShort()   const override { return (short)value;  }
        char   getAsChar()    const override { return (char)value;   }
    };
    template <typename T> NumberElement<T>::NumberElement(const T& value) : value(value)
    {
        if constexpr (std::is_same_v<T, int> || std::is_same_v<T, unsigned int> || std::is_same_v<T, size_t>) {
            type = JsonType::Integer;
        } else if constexpr (std::is_same_v<T, float>) {
            type = JsonType::Float;
        } else if constexpr (std::is_same_v<T, long>) {
            type = JsonType::Long;
        } else if constexpr (std::is_same_v<T, short>) {
            type = JsonType::Short;
        } else if constexpr (std::is_same_v<T, double>) {
            type = JsonType::Double;
        } else {
            type = JsonType::Char;
        }
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
        type = JsonType::Boolean;
    }


    class ArrayElement final : public JsonElement
    {
    private:
        JsonUtils::JsonArray array;
    
    public:
        explicit ArrayElement(JsonUtils::JsonArray array);
        ~ArrayElement() override {
            for(const JsonElement* element : array) { delete element; }
            array.clear();
        }
    
        JsonUtils::JsonArray getAsArray() const override { return array; }
    };
    inline ArrayElement::ArrayElement(JsonUtils::JsonArray array) : array(std::move(array))
    {
        type = JsonType::Array;
    }


    class ObjectElement final : public JsonElement
    {
    private:
        JsonUtils::JsonMap map;
    
    public:
        explicit ObjectElement(JsonUtils::JsonMap map);
        ~ObjectElement() override {
            for(const auto& it : map) { delete it.second; }
            map.clear();
        }
    
        JsonUtils::JsonMap getAsObject() const override { return map; }
    };
    inline ObjectElement::ObjectElement(JsonUtils::JsonMap map) : map(std::move(map))
    {
        type = JsonType::Object;
    }
}