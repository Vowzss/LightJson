#pragma once

#include <algorithm>
#include <string>
#include <sstream>

class StringUtils {
public:
	static std::string cleanup(const std::string& str) {
        std::ostringstream  oss;
        for (const char c : str) {
            switch (c) {
            case '\"':
                oss << "\\\"";
                break;
            case '\\':
                oss << "\\\\";
                break;
            case '/':
                oss << "\\/";
                break;
            case '\b':
                oss << "\\b";
                break;
            case '\f':
                oss << "\\f";
                break;
            case '\n':
                oss << "\\n";
                break;
            case '\r':
                oss << "\\r";
                break;
            case '\t':
                oss << "\\t";
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