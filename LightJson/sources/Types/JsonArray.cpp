#include "Includes/Types/JsonArray.h"

JsonArray::JsonArray(const std::string& pKey) : key(pKey)
{
}

void JsonArray::AddValue(const JsonElement& pValue)
{
    const int& index = map.empty() ? 0 : (int)map.size();
    map.insert({index, pValue});
}
