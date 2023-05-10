#pragma once

#include <stdexcept>

#include "JsonDeserializer.h"
#include "JsonElement.h"

namespace LightJson
{
    class JsonObject
    {
    private:
        JsonUtils::JsonMap members;

    public:
        JsonObject() {
            members = {};
        }

        JsonObject(const std::string& json) {
            members = JsonDeserializer::fromJson(json);
        }

        JsonObject(JsonUtils::JsonMap members) : members(std::move(members)) {}

        ~JsonObject() {
            for(const auto& it : members) {
                delete it.second;
            }
            members.clear();
        }
    
        JsonUtils::JsonMap getMembers() const {
            return members;
        }

        JsonElement* getMember(const std::string& key) {
            if(!hasKey(key)) {
                throw std::runtime_error("Key not found in object: " + key);
            }
            return members[key];
        }


        void setMember(const std::string& key, JsonElement* element) {
            members[key] = element;
        }

        bool hasKey(const std::string& key) const {
            return members.count(key) > 0;
        }
    };
}