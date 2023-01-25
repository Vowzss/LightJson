#include "JsonUtils.h"

#include "StringUtils.h"

std::string JsonUtils::StripKey(const std::string& raw)
{
    std::string member = StringUtils::StripAll(raw, '"');
    member = StringUtils::StripAll(member, ' ');

    if (StringUtils::Contains(member, ","))
        member = StringUtils::Strip(member, ",");

    return member;
}
