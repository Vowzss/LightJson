#pragma once

#include <fstream>
#include <string>

namespace LightJson
{
	class JsonReader
	{
	public:
		void Deserialize();

		void Open(const std::string& pFileName);
		void Close();

	private:
		std::ifstream file;
	};
}