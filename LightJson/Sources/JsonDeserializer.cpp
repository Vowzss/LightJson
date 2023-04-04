#include "../Includes/JsonDeserializer.hpp"

#include <iostream>

#include "../Includes/JsonObject.hpp"
#include "../Includes/StringUtils.h"

JsonUtils::JsonMap JsonDeserializer::fromJson(const std::string& json)
{
    std::unordered_map<std::string, JsonElement*> jsonObject;
    
    int depth = 0;
    size_t separatorIdx = 1; // to avoid char '{' at beginning of the json string

    if(json[0] != '{') {
        throw std::runtime_error("JSON string");
    }
    for (size_t i = 0; i < json.size(); ++i)
    {
        const char c = json[i];
        if(c == ',') {
            std::string string = json.substr(separatorIdx, i - separatorIdx);
            separatorIdx = i;
            JsonPair pair = parseString(string);
            jsonObject.insert(pair, element);
        }
    }
    
        /*switch (markdown) {
        case JsonMarkdown::START:
            if (c == '{') {
                markdown = JsonMarkdown::KEY;
            } else {
                throw std::runtime_error("JSON is not valid!");
            }
            break;
        case JsonMarkdown::KEY:
            if (c == '"') {
                markdown = JsonMarkdown::COLON;
            } else {
                throw std::runtime_error("JSON is not valid!");
            }
            break;
        case JsonMarkdown::COLON:
            if (c == ':') {
                markdown = JsonMarkdown::VALUE;
            } else {
                throw std::runtime_error("JSON is not valid!");
            }
            break;
        case JsonMarkdown::VALUE:
            if (c == '"') {
                value.clear();
                markdown = JsonMarkdown::COMMA;
            } else {
                value += c;
            }
            break;
        case JsonMarkdown::COMMA:
            if (c == ',') {
                jsonObject.insert(key, value);
                key.clear();
                markdown = JsonMarkdown::KEY;
            } else if (c == '}') {
                jsonObject.insert(key, value);
                markdown = JsonMarkdown::END;
            } else {
                throw std::runtime_error("JSON is not valid!");
            }
            break;
        case JsonMarkdown::END:
            /*if (!isspace(c)) {
                throw std::runtime_error("JSON is not valid!");
            }
            break;
        }
    }*/

    return jsonObject;
}

JsonDeserializer::JsonPair JsonDeserializer::parseString(const std::string& string)
{
    const size_t separatorIdx = string.find(':');
    const std::string key = StringUtils::removeQuotes(string.substr(0, separatorIdx-1));
    const std::string val = string.substr(separatorIdx+2, string.size()-separatorIdx-2);

    switch (val[0])
    {
    case '{':
        break;
    case '[': {
            const JsonElement array = parseArray(val);
            break;
        }
    case '"':
        return JsonPair(key, StringElement(StringUtils::removeQuotes(val)));
    case 't':
        return JsonPair(key, BooleanElement(true));
    case 'f':
        return JsonPair(key, BooleanElement(false));
    default:
        return JsonPair(key, NumberElement(std::stod(val)));
    }
}

JsonElement JsonDeserializer::parseArray(const std::string& string)
{

    return {};
}
