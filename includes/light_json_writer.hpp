#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace LightJson
{
	class JsonWriter
	{
	public:
		void Serialize();

		/**/
		bool Check(const std::string& p_FileName);
		void Create(const std::string& p_FileName);

		void Open(const std::string& p_FileName);
		void Close(const std::string& p_FileName);
		void Delete(const std::string& p_FileName);
		/**/

		/**/
		bool Check();

		void Open();
		void Close();
		void Delete();
		/**/

	private:
		std::ofstream json;

		std::string fileName;

		static std::vector<std::string> fileNames;
	};
}
