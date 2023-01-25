#include "StringUtils.h"

#include <algorithm>
#include <stdexcept>

bool StringUtils::Contains(const std::string& content, const std::string& value)
{
    return content.find(value) != std::string::npos;
}

std::string StringUtils::Strip(const std::string& content, const std::string& value)
{
    std::string cpy = content;
    const size_t foundPos = cpy.find(value);

    if (foundPos != std::string::npos)
        cpy.erase(foundPos, value.length());

    return cpy;
}

std::string StringUtils::StripAll(const std::string& content, char value)
{
    std::string cpy = content;
    cpy.erase(std::remove(cpy.begin(), cpy.end(), value), cpy.end());
    return cpy;
}

std::string StringUtils::ToLower(const std::string& value)
{
    std::string cpy = value;
    std::transform(cpy.begin(), cpy.end(), cpy.begin(), tolower);
    return cpy;
}

bool StringUtils::ToBool(const std::string& value)
{
    if (value == "0") return false;
    if (value == "1") return true;

    if (ToLower(value) == "true") return true;
    if (ToLower(value) == "false") return false;

    throw std::invalid_argument("Cannot convert STRING to BOOL");
}

int StringUtils::ToInt(const std::string& value)
{
    try
    {
        return std::stoi(value);
    }
    catch (std::invalid_argument& e)
    {
        throw std::invalid_argument(e.what());
    } catch (std::out_of_range& e)
    {
        throw std::out_of_range(e.what());
    }
}

float StringUtils::ToFloat(const std::string& value)
{
    try
    {
        return std::stof(value);
    }
    catch (std::invalid_argument& e)
    {
        throw std::invalid_argument(e.what());
    } catch (std::out_of_range& e)
    {
        throw std::out_of_range(e.what());
    }
}

double StringUtils::ToDouble(const std::string& value)
{
    try
    {
        return std::stod(value);
    }
    catch (std::invalid_argument& e)
    {
        throw std::invalid_argument(e.what());
    } catch (std::out_of_range& e)
    {
        throw std::out_of_range(e.what());
    }
}
