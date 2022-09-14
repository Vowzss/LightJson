#pragma once

#include <fstream>
#include <string>

namespace LightJson
{
	class JsonWriter
	{
	public:
		void Serialize();

		void Create(const std::string& p_FileName);
		void Delete();

		void Open();
		void Close();

	private:
		std::ofstream json;
		bool jsonExist;

		std::string jsonName;
	};
}
