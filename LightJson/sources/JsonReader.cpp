#include "includes/JsonReader.hpp"

#include <iostream>
#include <fstream>

#include "Includes/JsonUtils.h"
#include "Includes/StringUtils.h"

namespace LightJson
{
    void JsonReader::Deserialize()
    {
        if (content.str().empty())
        {
            std::cout << "File cannot be deserialized, Make sure it is opened beforehand!" << std::endl;
            return;
        }

        std::string line;
        int currentLine = 0;
        while (std::getline(content, line))
        {
            if (StringUtils::Contains(line, ": ["))
            {
                HandleArray(StringUtils::Strip(line, ": ["), currentLine);
            }
            currentLine++;
        }
    }

    void JsonReader::Open(const std::string& pFileName)
    {
        if (isInUse)
        {
            std::cout << "You opened another file without closing the previous one..." << std::endl;
            std::cout << "Previous file content is begin replaced by new one!" << std::endl;
        }

        isInUse = true;
        std::fstream fs(pFileName, std::ios_base::in);
        content << fs.rdbuf();
        fs.close();
    }

    void JsonReader::Close()
    {
        content.clear();
        isInUse = false;
    }

    JsonArray JsonReader::HandleArray(const std::string& arrayName, int& pCurrentLine)
    {
        JsonArray jsonArray = JsonArray(JsonUtils::StripKey(arrayName));

        std::string line;
        while (std::getline(content, line))
        {
            jsonArray.AddValue(JsonElement(JsonUtils::StripKey(line)));

            if (StringUtils::Contains(line, "],"))
            {
                pCurrentLine++;
                break;
            }

            if (StringUtils::Contains(line, "{"))
            {
            }
            else if (StringUtils::Contains(line, "},"))
            {
            }

            pCurrentLine++;
        }

        return jsonArray;
    }
}
