#include "../Includes/JsonDeserializer.hpp"

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

JsonElement JsonDeserializer::fromJson(const std::string& json)
{
    if (json.empty()) {
        throw std::runtime_error("Invalid JSON: empty string");
    }

    const char firstChar = json.front();
    if (firstChar == '{')
    {
        if (json.back() != '}') {
            throw std::runtime_error("Invalid JSON: missing closing brace in object");
        }

        std::unordered_map<std::string, JsonElement> object;
        size_t i = 1;
        while (i < json.length() - 1)
        {
            if (json[i] != '"') {
                throw std::runtime_error("Invalid JSON: missing quotes around object key");
            }

            const size_t keyEndPos = json.find('"', i + 1);
            if (keyEndPos == std::string::npos) {
                throw std::runtime_error("Invalid JSON: missing closing quotes around object key");
            }

            std::string key = fromJson(json.substr(i, keyEndPos - i)).getAsString();
            i = keyEndPos + 1;
            if (json[i] != ':') {
                throw std::runtime_error("Invalid JSON: missing colon after object key");
            }
            i++;

            size_t commaPos = json.find(',', i);
            if (commaPos == std::string::npos) {
                commaPos = json.length() - 1;
            }

            const size_t bracePos = json.find('}', i);
            if (bracePos == std::string::npos) {
                throw std::runtime_error("Invalid JSON: missing closing brace in object");
            }

            if (commaPos < bracePos) {
                object[key] = fromJson(json.substr(i, commaPos - i));
                i = commaPos + 1;
            }
            else {
                object[key] = fromJson(json.substr(i, bracePos - i));
                i = bracePos + 1;
                break;
            }
        }
        return {object};
    }
    
    if (firstChar == '[')
    {
        if (json.back() != ']') {
            throw std::runtime_error("Invalid JSON: missing closing bracket in array");
        }

        std::vector<JsonElement> array;
        
        size_t i = 1;
        while (i < json.length() - 1)
        {
            size_t commaPos = json.find(',', i);
            if (commaPos == std::string::npos) {
                commaPos = json.length() - 1;
            }
            
            const size_t bracketPos = json.find(']', i);
            if (bracketPos == std::string::npos) {
                throw std::runtime_error("Invalid JSON: missing closing bracket in array");
            }
            
            if (commaPos < bracketPos) {
                array.push_back(fromJson(json.substr(i, commaPos - i)));
                i = commaPos + 1;
            }
            else {
                array.push_back(fromJson(json.substr(i, bracketPos - i)));
                i = bracketPos + 1;
                break;
            }
        }
        return {array};
    }
    if (firstChar == '"' || (firstChar >= '0' && firstChar <= '9') || firstChar == '-') {
        return {json};
    }
    if (json.substr(0, 4) == "true") {
        return {true};
    }
    if (json == "false") {
        return {false};
    }
    if (json == "null") {
        return {};
    }
    
    {
        try {
            return {(std::stod(json))};
        }
        catch (std::invalid_argument& e) {
            throw std::runtime_error("Invalid JSON: unrecognized value type");
        }
    }

}