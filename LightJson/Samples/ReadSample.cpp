#include <sstream>
#include <fstream>

#include <iostream>

#include "../Includes/JsonObject.h"
#include "../Includes/StringUtils.h"

using namespace LightJson;

void ReadSample()
{
    const std::ifstream fs("Resources/Example.json");
    std::stringstream ss;
    ss << fs.rdbuf();
	
    JsonObject newObj(StringUtils::removeWhitespace(ss.str()));
    std::cout << newObj.getMember("country")->getAsString() << std::endl;
    std::cout << newObj.getMember("email from expression")->getAsString() << std::endl;
    std::cout << newObj.getMember("array")->getAsArray()[0]->getAsString() << std::endl;
}

//int main()
//{
//    ReadSample();
//}