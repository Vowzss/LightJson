<div align="center">

# LightJson
</div>

**LightJson is a lightweight json serialization and deserialization system originally made for saving and editing scenes data for a game engine project.**<br/>

# Run
Open **LightJson.sln** solution using Visual Studio (recommended version 2019) or Rider

# Usage
The architecture is very similar to it's implementation in Java, To create a json object simply instanciate it the following way.<br/>
```cpp
#include "Includes/JsonObject.hpp"
using namespace LightJson;

JsonObject obj; // Empty instanciate
JsonObject obj("{ "aObject": { "aDoubleValue": 2.351518 }, }") // Deserialize entry
```

JsonSerializer class:<br>
- toJson -> returns a string representing the JsonObject from a JsonObject entry.
- toFile -> writes the JsonObject as a string inside a specific file<br> 
PS: filename represents a relative path (ex: "JsonFiles/generated.json"), will create a file named generated.json inside JsonFiles folder.
- parseElement -> Method meant to be used by JsonSerializer only, does the whole conversion logic.
```cpp
class JsonSerializer {
public:
    static std::string toJson(const JsonObject* jsonObject);
    static void toFile(const JsonObject* jsonObject, const std::string& filename);

protected:
    static std::string parseElement(const JsonElement* jsonElement);
};
```
JsonDeserializer class<br>
- fromJson -> returns a JsonMap representing a constructed JsonObject from a string entry
- parseElement, parseArray, parseArrayElement -> Methods meant to be used by JsonDeserializer only, does the whole parsing logic.
```cpp
class JsonDeserializer {
public:
    static JsonUtils::JsonMap fromJson(const std::string& json);

protected:
    static JsonUtils::JsonPair parseElement     (const std::string& element);
    static ArrayElement*       parseArray       (const std::string& array);
    static JsonElement*        parseArrayElement(const std::string& element);
};
```

LightJson is  very permisive and easy to implement on ongoing projects, refer to **JsonHelper.h** and **JsonVirtual.h**, their usage are similar but the implementation differs.<br><br> 
Using JsonHelper, the serialization and deserialization logic are located outside the class.<br> 
That way you avoid touching your classes directly, helpful if you need to remove the said class in the future or LightJson library.
```cpp
template<typename T> class JsonHelper
{
public:
    static JsonElement* Serialize(const T& value);
    static T Deserialize(const LightJson::JsonElement* jsonElement);
};
```
An implementation exemple, 
```cpp
// Square.h
namespace LightJson {
    class JsonElement;
}

class Square
{
public:
    float size = 5;
    std::string name = "Square";

    Square();
    Square(const LightJson::JsonElement* jsonElement); // optional;
}

// Square.cpp or any cpp file
#include "Includes/JsonHelper.hpp"  // Access to Serialize and Deserialize methods
#include "Includes/JsonElement.hpp" // Access to StringElement, NumberElement, ObjectElement, ....
#include "Includes/JsonUtils.hpp"   // Access to JsonMap

template<> inline JsonElement* LightJson::JsonHelper<Square>::Serialize(const Square& value)
{
    JsonUtils::JsonMap map = {};
    map["size"] = new NumberElement<float>(value.size);
    map["name"] = new StringElement(value.name);
    return new ObjectElement(map);
}

template<> Square LightJson::JsonHelper<Square>::Deserialize(const LightJson::JsonElement* jsonElement)
{
    // If constructor handeling JsonElement*
    return Square(jsonElement);

    // get the element as a map for easy access to values;
    JsonUtils::JsonMap map = jsonElement->getAsObject();

    // Dummy deserialization
    Square object{};
    object.size = map["size"]->getAsFloat();
    object.name = map["name"]->getAsString();
    return object;

    // If constructor needs values when constructed
    return Square(map["size"]->getAsFloat(), map["name"]->getAsString());
}
```

Using JsonVirtual, the serialization and deserialization logic are located inside the class.
```cpp
class JsonVirtual
{
public:
    virtual ~JsonVirtual() = default;
    
    virtual JsonElement* Serialize  () const { return nullptr; }
    virtual void         Deserialize(const JsonElement* jsonElement) {}
};
```

An implementation exemple, your Square class will inherite from JsonVirtual, and you can simply override both methods.<br> 
Also works if your Square class inherits from an Object class that also happen to inherits from JsonVirtual and so on (basic c++ inheritance paradygm at this point).
```cpp
// Square.h
#include "Includes/JsonVirtual.hpp"

namespace LightJson {
    class JsonElement;
}

class Square : public LightJson::JsonVirtual
{
public:
    float size = 5;
    std::string name = "Square";

    // Refer to JsonHelper exemple implementation for serialiation & deserialization logic
protected:
    LightJson::JsonElement* Serialize() const                   override;
    void Deserialize(const LightJson::JsonElement* jsonElement) override;
};
```

# Other information
The JsonElement object is the entry point for everything, all elements inherits from the JsonElement class.<br>
Here is the current implementation of the ObjectElement class:
```cpp
class ObjectElement final : public JsonElement
{
private:
    JsonUtils::JsonMap map;

public:
    explicit ObjectElement(JsonUtils::JsonMap map);
    ~ObjectElement() override {
        for(const auto& it : map) { delete it.second; }
        map.clear();
    }

    JsonUtils::JsonMap getAsObject() const override { return map; }
};
```

As of now the library supports the following types:<br>
```cpp
enum class JsonType {
    Null,
    Boolean,
    Float,
    Double,
    Long,
    Short,
    Char,
    Integer,
    String,
    Array,
    Object
};
```

Easy bindings are available in **JsonUtils.h** for friendly usage experience when dealing with json's array & object
```cpp
typedef std::unordered_map<std::string, JsonElement*> JsonMap;
typedef std::vector<JsonElement*>                     JsonArray;

// Only used by the serializer/deserializer, you don't need to use it on a regular basis
typedef std::pair<std::string, JsonElement*>          JsonPair; 
```

# Exemples
You can head to the following folder to have a better view of the whole library in action.<br/>
&nbsp;&nbsp; -> .cpp files located in Sources/<br/>
&nbsp;&nbsp; -> .h files located in Includes/<br/>

Samples are located in Samples/ folder<br/>
- CreateSample.cpp -> Creation of a JsonObject from hand. Generated json located at Resources/CreateSample.json.<br>
```json
{
    "name": "John Doe",
    "age": 17,
    "isStudent": true,
    "classes": [
        {
            "Science": [
                "Mathematics",
                "Physics",
                "Chemistry"
            ],
            "Literature": [
                "English"
            ]
        },
        "English",
        "French",
        "Geography"
    ],
    "grades": {
        "Mathematics": "A",
        "Physics": "D",
        "English": "B"
    }
}
```
- ReadSample.cpp -> Reading from a json file. Json file located at Resources/ReadSample.json.<br>
- HelperSample.cpp & HelperSample.h -> A complexe but regular implementation of the library.<br>
Generated json files located under the same Resources/ folder, respectively named **'HelperSample1.json'**, **'HelperSample2.json'** and **'HelperSample3.json'.**<br>

Here is the current generated json by running the third sample **HelperSample3.json**:
```cpp
JsonObject* obj3 = new JsonObject();
obj3->setMember("trickyObjTest", JsonHelper<TrickyObject>::Serialize(TrickyObject()));
JsonSerializer::toFile(obj3, "Resources/HelperSample3.json");
delete obj3; obj3 = nullptr;
```

```json
{
    "trickyObjTest": {
        "aObject": {
            "aDoubleValue": 2.351518
        },
        "aLongValue": 56111,
        "aOtherObject": {
            "aIntValue": 152881,
            "aStringValue": "AString",
            "aFloatValue": 0.515152
        }
    }
}
```

# Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.<br/>
Please make sure to update tests as appropriate.<br/>