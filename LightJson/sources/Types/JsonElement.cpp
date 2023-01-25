#include "Includes/Types/JsonElement.h"

JsonElement::JsonElement(const std::string& pValue) : value(pValue)
{
}

JsonElement::~JsonElement()
{
    delete child;
}
