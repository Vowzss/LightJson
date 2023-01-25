#pragma once

#include <string>

class StringUtils
{
public:
    static bool Contains(const std::string& content, const std::string& value);

    static std::string Strip(const std::string& content, const std::string& value);

    static std::string StripAll(const std::string& content, char value);

    static std::string ToLower(const std::string& value);

    static bool ToBool(const std::string& value);

    static int ToInt(const std::string& value);

    static float ToFloat(const std::string& value);

    static double ToDouble(const std::string& value);
};
