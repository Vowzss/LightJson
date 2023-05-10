#pragma once

#include <string>
#include <sstream>

namespace LightJson
{
	class StringUtils {
	public:
		static std::string cleanup(const std::string& str) {
			std::ostringstream  oss;
			for (const char c : str) {
				switch (c) {
				case '\b':
				case '\f':
				case '\n':
				case '\r':
				case '\t':
					break;
				default:
					oss << c;
					break;
				}
			}
			return oss.str();
		}

		static std::string removeWhitespace(std::string str)
		{
			bool prevCharWasSpace = false;
			for (size_t i = 0; i < str.size(); i++)
			{
				const char c = str[i];
				if (c < 0 || std::isspace(c))
				{
					if (prevCharWasSpace || c == '\n' || c < 0) {
						str.erase(str.begin()+i);
						--i;
					}
					else {
						str[i] = ' ';
					}
					prevCharWasSpace = true;
				}
				else {
					prevCharWasSpace = false;
				}
			}
			return str;
		}

		static std::string removeQuotes(std::string str)
		{
			str.erase(std::remove(str.begin(), str.end(), '\"'), str.end());
			return str;
		}
	};
}