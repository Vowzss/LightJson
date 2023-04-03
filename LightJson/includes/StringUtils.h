#pragma once

#include <string>
#include <sstream>

class StringUtils {
public:
	static std::string cleanup(const std::string& str) {
        std::ostringstream  oss;
        for (const char c : str) {
            switch (c) {
            case '\"':
                oss << "\\\"";
                break;
            case '\\':
                oss << "\\\\";
                break;
            case '/':
                oss << "\\/";
                break;
            case '\b':
                oss << "\\b";
                break;
            case '\f':
                oss << "\\f";
                break;
            case '\n':
                oss << "\\n";
                break;
            case '\r':
                oss << "\\r";
                break;
            case '\t':
                oss << "\\t";
                break;
            default:
                oss << c;
                break;
            }
        }
        return oss.str();
    }
};