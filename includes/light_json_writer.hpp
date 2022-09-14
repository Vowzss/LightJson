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

		void Open(const std::string& p_FileName);
		void Close();

	private:
		static std::ofstream json;
		static bool jsonExist;
	};
}
