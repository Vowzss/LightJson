#include <fstream>
#include <iostream>

#include "../Includes/StringUtils.h"
#include "../Includes/JsonSerializer.h"
#include "../Includes/JsonObject.h"

using namespace LightJson;

std::string JsonSerializer::toJson(const JsonObject* jsonObject)
{
    std::string jsonString;

    const auto members = jsonObject->getMembers();
    for (auto member = members.begin(); member != members.end(); ++member)
    {
        const bool&        isEnd     = member == --members.end();
        const std::string& startLine = "\"" + member->first + "\"" + ": ";
        const std::string& endLine   = isEnd ? "" : ",";

        const std::string& line = parseElement(member->second);
        jsonString.append(startLine).append(line).append(endLine);
    }
    
    return "{" + jsonString + "}";
}

void JsonSerializer::toFile(const JsonObject* jsonObject, const std::string& filename)
{
    std::ofstream outfile(filename);
    outfile << toJson(jsonObject);
    outfile.close();

    std::cout << "Saved JsonObject. Filename: " << filename.c_str() << std::endl;
}

std::string JsonSerializer::parseElement(const JsonElement* jsonElement)
{
    std::string json;
    std::ostringstream oss;
    
    switch (jsonElement->getType())
    {
        case JsonType::Null:
                return "";

        case JsonType::Boolean:
            return jsonElement->getAsBoolean() ? "true" : "false";

        case JsonType::Float:
            return std::to_string(jsonElement->getAsFloat());

        case JsonType::Double:
            return std::to_string(jsonElement->getAsDouble());

        case JsonType::Long:
            return std::to_string(jsonElement->getAsLong());

        case JsonType::Short:
            return std::to_string(jsonElement->getAsShort());
        
        case JsonType::Char:
            return std::to_string(jsonElement->getAsChar());

        case JsonType::Integer:
            return std::to_string(jsonElement->getAsInteger());

        case JsonType::String:
            return "\"" + StringUtils::cleanup(jsonElement->getAsString()) + "\"";

        case JsonType::Array: {
                oss << "[";
                const auto& array = jsonElement->getAsArray();
                for (std::size_t i = 0; i < array.size(); ++i) {
                    oss << parseElement(array[i]);
                    if (i != array.size() - 1) {
                        oss << ",";
                    }
                }
                oss << "]";
                return oss.str();
        }

        case JsonType::Object: {
                oss << '{';
                bool first = true;
                JsonUtils::JsonMap map = jsonElement->getAsObject();
                for (auto it = map.begin(); it != map.end(); ++it) {
                    if (!first) { oss << ','; }
                    oss << "\"" << it->first  << "\"" << ":" << " " << parseElement(it->second);
                    first = false;
                }
                oss << '}';
                return oss.str();
        }

        default: throw std::runtime_error("Invalid JSON value type");
    }
}
