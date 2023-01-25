#pragma once

#include <sstream>
#include <string>

#include "Types/JsonArray.h"

namespace LightJson
{
	class JsonReader
	{
	public:
		void Deserialize();

		void Open(const std::string& pFileName);
		void Close();
	private:
		JsonArray HandleArray(const std::string& arrayName, int& currentLine);
		
	private:
		std::stringstream content;
		bool isInUse = false;
	};
}
