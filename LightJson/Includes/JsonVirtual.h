#pragma once

namespace LightJson {
	class JsonObject;

	class JsonVirtual
	{
	public:
		virtual void serialize(JsonObject& jsonObject) = 0;
		virtual void deserialize(JsonObject& jsonObject) = 0;
	};
}

