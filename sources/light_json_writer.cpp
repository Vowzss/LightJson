#include "includes/light_json_writer.hpp"

#include <iostream>
#include <filesystem>
#include <cstdio>

#define LOGGER "[JsonWriter] "

namespace LightJson
{
	std::vector<Json> JsonWriter::jsons = {};

	JsonWriter::JsonWriter(const std::string& p_Name) {
		json = Json(p_Name);
	}

	void JsonWriter::setLogger() {
		logger = !logger;
	}

	void JsonWriter::Create(const std::string& p_FileName) {
		json.object.name = p_FileName;
		jsons.emplace_back(json);

		if (!Check(p_FileName, logger)) {
			if (logger) std::cout << LOGGER << "Creating \"" << p_FileName << "\" ..." << std::endl;
			std::ofstream outfile(p_FileName);
			outfile.close();
		}
	}

	/*void JsonWriter::Serialize() {
		if (!json.is_open()) {
			std::cout << LOGGER << "File cannot be serialized, Make sure it is openned beforehand!" << std::endl;
			return;
		}
	}*/

	void JsonWriter::Open(const std::string& p_FileName) {
		if (Check(p_FileName, false)) {
			if (logger) std::cout << LOGGER << "Openning \"" << p_FileName << "\"..." << std::endl;
			json.object.file.open(p_FileName);
		}
	}
	void JsonWriter::Close(const std::string& p_FileName) {
		if (Check(p_FileName, false)) {
			if (logger) std::cout << LOGGER << "Closing \"" << p_FileName << "\"..." << std::endl;
			json.object.file.close();
		}
	}
	void JsonWriter::Delete(const std::string& p_FileName) {
		if (Check(p_FileName, false)) {
			if (logger) std::cout << LOGGER << "Deleting \"" << p_FileName << "\"..." << std::endl;
			json.object.file.flush();
			json.object.file.close();

			std::remove(p_FileName.c_str());
		}
	}
	bool JsonWriter::Check(const std::string& p_FileName, const bool& p_log) {
		if(p_log) std::cout << LOGGER << "Checking \"" << p_FileName << "\"..." << std::endl;
		std::ifstream f(p_FileName.c_str());

		if (f.good()) {
			if (p_log) std::cout << LOGGER << "\"" << p_FileName << "\" already exist!" << std::endl;
			return true;
		}
		else {
			if (p_log) std::cout << LOGGER << "\"" << p_FileName << "\" doesn't exist..." << std::endl;
			return false;
		}
	}

	void JsonWriter::Open() {
		if (Check(json.object.name, false)) {
			if (logger) std::cout << LOGGER << "Openning \"" << json.object.name << "\"..." << std::endl;
			json.object.file.open(json.object.name);
		}
	}
	void JsonWriter::Close() {
		if (Check(json.object.name, false)) {
			json.object.file.close();
		}
	}
	void JsonWriter::Delete() {
		if (logger) std::cout << LOGGER << "Deleting \"" << json.object.name << "\"..." << std::endl;
		json.object.file.flush();
		json.object.file.close();

		std::remove(json.object.name.c_str());
	}
	bool JsonWriter::Check(const bool& p_log) {
		if (p_log) std::cout << "Checking \"" << json.object.name << "\" ..." << std::endl;
		std::ifstream f(json.object.name.c_str());

		if (f.good()) {
			if (p_log) std::cout << LOGGER << "\"" << json.object.name << "\" already exist!" << std::endl;
			return true;
		}
		else {
			if (p_log) std::cout << LOGGER << "\"" << json.object.name << "\" not detected..." << std::endl;
			return false;
		}
	}
}
