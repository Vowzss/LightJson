#pragma once

#include "JsonUtils.h"

namespace LightJson {
	class JsonObject;
	class JsonElement;
	
	class JsonVirtual
	{
	public:
		virtual ~JsonVirtual() = default;
		
		virtual JsonElement* Serialize()					   { return nullptr; }
		virtual void		 Serialize(JsonObject& jsonObject) {}
		
		virtual void Deserialize(JsonObject& jsonObject)	  {}
		virtual void Deserialize(JsonUtils::JsonMap& jsonMap) {}
	};
}

