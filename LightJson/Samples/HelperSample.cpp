#include "HelperSample.h"

#include <fstream>

#include "../Includes/JsonHelper.h"
#include "../Includes/JsonObject.h"
#include "../Includes/JsonSerializer.h"

using namespace LightJson;

int main() {

}

/*
void HelperSample()
{
    AnObject objTest{};
    JsonObject* obj1 = new JsonObject();
    obj1->setMember("objTest", JsonHelper::Serialize<AnObject>(objTest));

    std::ofstream outfile1("Resources/HelperSample1.json");
    outfile1 << JsonSerializer::toJson(obj1);
    outfile1.close();
    
    AnotherObject anotherObjTest{};
    JsonObject* obj2 = new JsonObject();
    // you can use either one depending on your own implementation
    obj2->setMember("anotherObjTest", anotherObjTest.Serialize());
    //anotherObjTest.Serialize(*obj2);
    std::ofstream outfile2("Resources/HelperSample2.json");
    outfile2 << JsonSerializer::toJson(obj2);
    outfile2.close();

    
    TrickyObject trickyObjTest{};
    JsonObject* obj3 = new JsonObject();
    obj3->setMember("trickyObjTest", JsonHelper::Serialize<TrickyObject>(trickyObjTest));
    std::ofstream outfile3("Resources/HelperSample3.json");
    outfile2 << JsonSerializer::toJson(obj3);
    outfile2.close();
}

// inner serialization of AnotherObject class example

// Serialization example returning a JsonElement* for future usage
JsonElement* AnotherObject::Serialize() const
{
    JsonUtils::JsonMap map = {};
    map["aStringValue"] = new StringElement(aStringValue);
    map["aFloatValue"]  = new NumberElement<float>(aFloatValue);
    map["aIntValue"]    = new NumberElement<int>(aIntValue);

    return new ObjectElement(map);
}

// Serialization example directly adding inside an existing JsonObject
void AnotherObject::Serialize(JsonObject& jsonObject) const
{
    // Two methods for this one, either serialize directly and add to jsonObject
    // or
    // implement "JsonElement* Serialize()" then call it inside

    /*JsonUtils::JsonMap map = {};
    map["aStringValue"] = new StringElement(aStringValue);
    map["aFloatValue"]  = new NumberElement<float>(aFloatValue);
    map["aIntValue"]    = new NumberElement<int>(aIntValue);

    jsonObject.setMember("AnotherObject", new ObjectElement(map));
    
    jsonObject.setMember("AnotherObject", Serialize());
}

// Deserialization example
void AnotherObject::Deserialize(JsonObject& jsonObject)
{
    JsonUtils::JsonMap map = jsonObject.getMember("AnotherObject")->getAsObject();

    aStringValue = map["aStringValue"]->getAsString();
    aFloatValue  = map["aFloatValue"]->getAsFloat();
    aIntValue    = map["aIntValue"]->getAsInteger();
}
*/