#include "includes/light_json_writer.hpp"

#include <iostream>
#include <filesystem>

namespace LightJson
{
	void JsonWriter::Create(const std::string& p_FileName) {
		if (std::filesystem::exists(p_FileName)) {
			jsonName = p_FileName;
			std::cout << "Json file detected, aborting!" << std::endl;
			jsonExist = true;
		}
		else {
			jsonName = "undifined";
			std::cout << "Json file not detected..." << std::endl;
			jsonExist = false;
		}
	}

	void JsonWriter::Delete() {
		json.flush();
		json.close();
	}

	void JsonWriter::Serialize() {
		if (!json.is_open()) {
			std::cout << "File cannot be serialized, Make sure it is openned beforehand!" << std::endl;
			return;
		}
	}

	void JsonWriter::Open() {
		if (jsonName == "undifined" || "") return;

		std::cout << "Openning json file..." << std::endl;
		json.open(jsonName);
	}

	void JsonWriter::Close() {
		if (jsonName == "undifined" || "") return;

		std::cout << "Closing json file..." << std::endl;
		json.close();
	}
}
