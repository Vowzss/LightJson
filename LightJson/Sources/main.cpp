#include <iostream>

#include "../Includes/JsonObject.hpp"

int main(int argc, char* argv[]) {
	JsonObject obj;
	obj.setElement("name", "John Doe");
	obj.setElement("age", static_cast<double>(30));
	obj.setElement("isStudent", false);
	
	std::string json = obj.toJson();
	std::cout << json << std::endl;
	
	JsonObject newObj(json);
	std::cout << newObj.getElement("name").getAsString() << std::endl;
	std::cout << newObj.getElement("age").getAsNumber() << std::endl;
	std::cout << newObj.getElement("isStudent").getAsBoolean() << std::endl;

	return 0;
}