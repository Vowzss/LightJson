#include "../Includes/JsonObject.hpp"
#include "../Includes/StringUtils.h"

using namespace LightJson;

JsonUtils::JsonMap JsonDeserializer::fromJson(const std::string& json)
{
    JsonUtils::JsonMap jsonObject;
    
    int depth = 0;
    size_t separatorIdx = 0;

    if(json[0] != '{') {
        throw std::runtime_error("JSON format error");
    }
    
    for (size_t i = 1; i < json.size(); ++i)
    {
        switch (json[i])
        {
            case '{':
            case '[':
                ++depth;
                break;
            
            case '}':
            case ']':
                --depth;
                break;
            
            case ',': {
                if (depth > 0) break;
                const std::string string       = json.substr(separatorIdx+1, i-separatorIdx-1);
                const JsonUtils::JsonPair pair = parseElement(string);
                jsonObject[pair.first]         = pair.second;
                separatorIdx                   = i;
                break;
            }
            default: break;
        }
        
        if (depth < 0)
        {
            const std::string string       = json.substr(separatorIdx+1, i-separatorIdx-1);
            const JsonUtils::JsonPair pair = parseElement(string);
            jsonObject[pair.first]         = pair.second;
            break;
        }
    }

    return jsonObject;
}

JsonUtils::JsonPair JsonDeserializer::parseElement(const std::string& element)
{
    const size_t separatorIdx = element.find(':');
    const std::string key     = StringUtils::removeQuotes(element.substr(0, separatorIdx-1));
    const std::string val     = element.substr(separatorIdx+2, element.size()-separatorIdx-2);

    if(val.empty()) {
        throw std::runtime_error("String is null or empty");
    }
    
    switch (val[0])
    {
        case '{':
            return JsonUtils::makeJsonPair(key, new ObjectElement(fromJson(val)));
        case '[':
            return JsonUtils::makeJsonPair(key, parseArray(val));
        case '"':
            return JsonUtils::makeJsonPair(key, new StringElement(StringUtils::removeQuotes(val)));
        case 't':
            return JsonUtils::makeJsonPair(key, new BooleanElement(true));
        case 'f':
            return JsonUtils::makeJsonPair(key, new BooleanElement(false));
        default:
            return JsonUtils::makeJsonPair(key, new NumberElement(std::stod(val)));
    }
}

ArrayElement* JsonDeserializer::parseArray(const std::string& array)
{
    std::vector<JsonElement*> values;
    
    int depth = 0;
    size_t separatorIdx = 0;

    if(array[0] != '[') {
        throw std::runtime_error("Array format error");
    }
    
    for (size_t i = 1; i < array.size(); ++i)
    {
        switch (array[i])
        {
        case '{':
        case '[':
            ++depth;
            break;
            
        case '}':
        case ']':
            --depth;
            break;
            
        case ',': {
                if (depth > 0) break;
                const std::string string = array.substr(separatorIdx+1, i-separatorIdx-1);
                values.emplace_back(parseArrayElement(string));
                separatorIdx = i;
                break;
        }
        default: break;
        }
        
        if (depth < 0)
        {
            const std::string string = array.substr(separatorIdx+1, i-separatorIdx-1);
            values.emplace_back(parseArrayElement(string));
            break;
        }
    }
    return new ArrayElement(values);
}

JsonElement* JsonDeserializer::parseArrayElement(const std::string& element)
{
    if(element.empty()) {
        throw std::runtime_error("Array element is null or empty");
    }
    
    switch (element[0])
    {
        case '{':
            return new ObjectElement(fromJson(element));
        case '[':
            return parseArray(element);
        case '"':
            return new StringElement(StringUtils::removeQuotes(element));
        case 't':
            return new BooleanElement(true);
        case 'f':
            return new BooleanElement(false);
        default:
            return new NumberElement(std::stod(element));
    }
}
