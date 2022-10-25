#pragma once

#include "includes/json.hpp"
#include <vector>

namespace LightJson
{
	class JsonWriter
	{
	public:
		JsonWriter(const std::string& p_Name);

		void setLogger();

		bool Check(const std::string& p_FileName, const bool& p_log);
		void Create(const std::string& p_FileName);

		void Open(const std::string& p_FileName);
		void Close(const std::string& p_FileName);
		void Delete(const std::string& p_FileName);

		bool Check(const bool& p_log);

		void Open();
		void Close();
		void Delete();

	private:
		Json json;

		bool logger = false;
		static std::vector<Json> jsons;
	};
}
