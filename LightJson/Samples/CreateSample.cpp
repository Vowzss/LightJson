#include <fstream>
#include <iostream>

#include "../Includes/JsonObject.h"
#include "../Includes/JsonSerializer.h"
#include "../Includes/StringUtils.h"

using namespace LightJson;

void CreateSample() {
	JsonObject* jsonObject = new JsonObject();
	jsonObject->setMember("name", new StringElement("John Doe"));
	jsonObject->setMember("age", new NumberElement<int>(17));
	jsonObject->setMember("isStudent", new BooleanElement(true));

	jsonObject->setMember("classes", new ArrayElement(
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

	jsonObject->setMember("grades", new ObjectElement(
		{
			{ "Mathematics", new StringElement("A") },
			{ "Physics", new StringElement("D") },
			{ "English", new StringElement("B") },
		})
		);

	JsonSerializer::toFile(jsonObject, "Resources/CreateSample.json");

	delete jsonObject;
	jsonObject = nullptr;
}

//int main() {
//	CreateSample();
//}
