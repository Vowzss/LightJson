#include <fstream>
#include <iostream>

#include "../Includes/JsonObject.hpp"
#include "../Includes/JsonSerializer.hpp"
#include "../Includes/StringUtils.h"

using namespace LightJson;

int main() {
	JsonObject* obj = new JsonObject();
	obj->setMember("name", new StringElement("John Doe"));
	obj->setMember("age",  new NumberElement(17));
	obj->setMember("isStudent", new BooleanElement(true));
	
	obj->setMember("classes", new ArrayElement(
		{
			new ObjectElement(
				{
					{ "Science", new ArrayElement(
						{
							new StringElement("Mathematics"),
							new StringElement("Physics"),
						    new StringElement("Chemistry"),
						}),
					},
					{ "Literature", new ArrayElement(
						{
							new StringElement("English"),
						}),
					},
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

	std::ifstream fs("Resources/test.json");
	std::stringstream ss;
	ss << fs.rdbuf();
	
	JsonObject newObj(StringUtils::removeWhitespace(ss.str()));
	std::cout << newObj.getMember("country")->getAsString() << std::endl;
	std::cout << newObj.getMember("email from expression")->getAsString() << std::endl;
	std::cout << newObj.getMember("array")->getAsArray()[0]->getAsString() << std::endl;

	return 0;
}
