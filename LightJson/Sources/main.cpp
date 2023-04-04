#include <iostream>

#include "../Includes/JsonObject.hpp"
#include "../Includes/JsonSerializer.hpp"

int main(int argc, char* argv[]) {
	JsonObject* obj = new JsonObject();
	obj->setMember("name", new StringElement("John Doe"));
	obj->setMember("age",  new NumberElement(17));
	obj->setMember("isStudent", new BooleanElement(true));
	
	obj->setMember("classes", new ArrayObject(
		{
			new ObjectElement(
				{
					{ "Science", new ArrayObject(
						{
							new StringElement("Mathematics"),
							new StringElement("Physics"),
						    new StringElement("Chemistry"),
						}),
					}
				}),
			new StringElement("English"),
			new StringElement("French"),
			new StringElement("Geography"),
		})
	);
	
	obj->setMember("grades", new ObjectElement(
		{
			{ "Mathematics", new StringElement("A") },
			{ "Physics", new StringElement("D") },
			{ "English", new StringElement("B") },
		})
	);
	
	const std::string json = JsonSerializer::toJson(obj);
	std::cout << json << std::endl;
	
	JsonObject newObj(json);
	std::cout << newObj.getMember("name")->getAsString() << std::endl;
	std::cout << newObj.getMember("age")->getAsNumber() << std::endl;
	std::cout << newObj.getMember("isStudent")->getAsBoolean() << std::endl;

	return 0;
}