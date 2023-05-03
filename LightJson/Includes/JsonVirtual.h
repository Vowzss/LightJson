#pragma once

#include "JsonUtils.h"

namespace LightJson {
	class JsonObject;
	class JsonElement;
	
	class JsonVirtual
	{
	public:
		virtual ~JsonVirtual() = default;
		
		virtual JsonElement* Serialize()					   const { return nullptr; }
		virtual void		 Serialize(JsonObject& jsonObject) const {}
		
		virtual void Deserialize(JsonObject& jsonObject)	   {}
		virtual void Deserialize(JsonUtils::JsonMap& jsonMap)  {}
	};
}

