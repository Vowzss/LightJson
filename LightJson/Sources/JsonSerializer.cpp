#include "../Includes/JsonSerializer.hpp"
#include "../Includes/StringUtils.h"

#include <sstream>
#include <iomanip>

std::string JsonSerializer::toJson(const JsonElement* element)
{
    std::ostringstream oss;

    switch (element->getType()) {
        case JsonType::Null:
            return "null";

        case JsonType::String:
            return "\"" + StringUtils::cleanup(element->getAsString()) + "\"";

        case JsonType::Number:
            return std::to_string(element->getAsNumber());

        case JsonType::Boolean:
            return element->getAsBoolean() ? "true" : "false";

        case JsonType::Array: {
            std::ostringstream out;
            out << "[";
            auto array = element->getAsArray();
            for (std::size_t i = 0; i < array.size(); ++i) {
                out << toJson(array[i]);
                if (i != array.size() - 1) {
                    out << ",";
                }
            }
            out << "]";
            return out.str();
        }

        case JsonType::Object:
        {
            oss << '{';
            bool first = true;
            for (auto it = element->getAsObject().begin(); it != element->getAsObject().end(); ++it) {
                if (!first) {
                    oss << ',';
                }
                oss << it->first << ':' << toJson(it->second);
                first = false;
            }
            oss << '}';
            return oss.str();
        }

        default:
            throw std::runtime_error("Invalid JSON value type");
    }
}
