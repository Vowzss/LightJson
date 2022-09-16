#include "includes/light_json_writer.hpp"

#include <iostream>
#include <filesystem>
#include <cstdio>

namespace LightJson
{
	std::vector<std::string> JsonWriter::fileNames = {};

	void JsonWriter::Create(const std::string& p_FileName) {
		fileName = p_FileName;
		fileNames.emplace_back(fileName);

		if (!Check(p_FileName)) {
			std::cout << "Creating \"" << p_FileName << "\" ..." << std::endl;
			std::ofstream outfile(p_FileName);
			outfile.close();
		}
	}

	void JsonWriter::Serialize() {
		if (!json.is_open()) {
			std::cout << "File cannot be serialized, Make sure it is openned beforehand!" << std::endl;
			return;
		}
	}

	void JsonWriter::Open(const std::string& p_FileName) {
		std::cout << "Openning \"" << p_FileName << "\"..." << std::endl;
		json.open(p_FileName);
	}
	void JsonWriter::Close(const std::string& p_FileName) {
		std::cout << "Closing \"" << p_FileName << "\"..." << std::endl;
		json.close();
	}
	void JsonWriter::Delete(const std::string& p_FileName) {
		std::cout << "Deleting \"" << p_FileName << "\"..." << std::endl;
		json.flush();
		json.close();

		std::remove(p_FileName.c_str());
	}
	bool JsonWriter::Check(const std::string& p_FileName) {
		std::cout << "Checking \"" << p_FileName << "\" ..." << std::endl;
		std::ifstream f(p_FileName.c_str());

		if (f.good()) {
			std::cout << "\"" << p_FileName << "\" already exist!" << std::endl;
			return true;
		}
		else {
			std::cout << "\"" << p_FileName << "\" doesn't exist..." << std::endl;
			return false;
		}
	}

	void JsonWriter::Open() {
		std::cout << "Openning \"" << fileName << "\"..." << std::endl;
		json.open(fileName);
	}
	void JsonWriter::Close() {
		std::cout << "Closing \"" << fileName << "\"..." << std::endl;
		json.close();
	}
	void JsonWriter::Delete() {
		std::cout << "Deleting \"" << fileName << "\"..." << std::endl;
		json.flush();
		json.close();

		std::remove(fileName.c_str());
	}
	bool JsonWriter::Check() {
		std::cout << "Checking \"" << fileName << "\" ..." << std::endl;
		std::ifstream f(fileName.c_str());

		if (f.good()) {
			std::cout << "\"" << fileName << "\" already exist!" << std::endl;
			return true;
		}
		else {
			std::cout << "\"" << fileName << "\" not detected..." << std::endl;
			return false;
		}
	}
}
