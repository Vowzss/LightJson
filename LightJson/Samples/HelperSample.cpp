#include "HelperSample.h"

#include <fstream>

#include "../Includes/JsonHelper.h"
#include "../Includes/JsonObject.h"
#include "../Includes/JsonSerializer.h"

using namespace LightJson;

// outter serialization of AnObject class example
template<> inline JsonElement* LightJson::JsonHelper<AnObject>::Serialize(const AnObject& value)
{
    JsonUtils::JsonMap map = {};
    map["aDoubleValue"] = new NumberElement<double>(value.aDoubleValue);
    return new ObjectElement(map);
}

// outter deserialization of AnObject class example
template<> AnObject LightJson::JsonHelper<AnObject>::Deserialize(const LightJson::JsonElement* jsonElement)
{
    JsonUtils::JsonMap map = jsonElement->getAsObject();

    AnObject object{};
    object.aDoubleValue = map["aDoubleValue"]->getAsDouble();
    return object;
}

// outter serialization of TrickyObject class example
template<> inline JsonElement* LightJson::JsonHelper<TrickyObject>::Serialize(const TrickyObject& value)
{
    JsonUtils::JsonMap map = {};
    map["aLongValue"] = new NumberElement<long>(value.aLongValue);
    map["aObject"] = JsonHelper<AnObject>::Serialize(value.aObject);
    map["aOtherObject"] = value.aOtherObject.Serialize();
    return new ObjectElement(map);
}


// outter deserialization of TrickyObject class example
template<> TrickyObject LightJson::JsonHelper<TrickyObject>::Deserialize(const LightJson::JsonElement* jsonElement)
{
    JsonUtils::JsonMap map = jsonElement->getAsObject();

    TrickyObject object{};
    object.aLongValue = map["aLongValue"]->getAsDouble();
    object.aObject = JsonHelper<AnObject>::Deserialize(map["aObject"]);

    // here we create a temporary AnotherObject object to access it's deserialize method 
    // (if args required pass them if possible or create custom constructor taking a 'JsonElement*' arg)
    AnotherObject anotherObject{};
    anotherObject.Deserialize(map["aOtherObject"]);
    object.aOtherObject = anotherObject;
    return object;
}


void HelperSample()
{
    JsonObject* obj1 = new JsonObject();
    obj1->setMember("objTest", JsonHelper<AnObject>::Serialize(AnObject()));
    JsonSerializer::toFile(obj1, "Resources/HelperSample1.json");
    delete obj1; obj1 = nullptr;
    
    JsonObject* obj2 = new JsonObject();
    obj2->setMember("anotherObjTest", AnotherObject().Serialize());

    JsonSerializer::toFile(obj2, "Resources/HelperSample2.json");
    delete obj2; obj2 = nullptr;
    
    JsonObject* obj3 = new JsonObject();
    obj3->setMember("trickyObjTest", JsonHelper<TrickyObject>::Serialize(TrickyObject()));
    JsonSerializer::toFile(obj3, "Resources/HelperSample3.json");
    delete obj3; obj3 = nullptr;
}

// inner serialization of AnotherObject class example
JsonElement* AnotherObject::Serialize() const
{
    JsonUtils::JsonMap map = {};
    map["aStringValue"] = new StringElement(aStringValue);
    map["aFloatValue"]  = new NumberElement<float>(aFloatValue);
    map["aIntValue"]    = new NumberElement<int>(aIntValue);

    return new ObjectElement(map);
}

// inner deserialization of AnotherObject class example
void AnotherObject::Deserialize(const LightJson::JsonElement* jsonElement)
{
    JsonUtils::JsonMap map = jsonElement->getAsObject();

    aStringValue = map["aStringValue"]->getAsString();
    aFloatValue  = map["aFloatValue"]->getAsFloat();
    aIntValue    = map["aIntValue"]->getAsInteger();
}

int main() {
    HelperSample();
}