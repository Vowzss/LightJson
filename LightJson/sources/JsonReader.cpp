#include "includes/JsonReader.hpp"

#include <iostream>

namespace LightJson {
	void JsonReader::Deserialize() {
		if (!file.is_open()) {
			std::cout << "File cannot be deserialized, Make sure it is opened beforehand!" << std::endl;
			return;
		}

		std::string line;
		while (file) {
			std::getline(file, line);
			std::cout << line << ": " << file.tellg() << '\n';
		}
	}

	void JsonReader::Open(const std::string& pFileName) {
		if(file.is_open())
		{
			std::cout << "You cannot open another file while one is already opened!" << std::endl;
			std::cout << "You can either create a new JsonReader instance or close previous file!" << std::endl;
			return;
		}
		file.open(pFileName);
	}

	void JsonReader::Close() {
		file.close();
	}
}