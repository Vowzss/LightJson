#pragma once

#include <fstream>
#include <string>

namespace LightJson
{
	class JsonReader
	{
	public:
		void Deserialize();

		void Open(const std::string& p_FileName);
		void Close();

	private:
		static std::ifstream json;
	};
}