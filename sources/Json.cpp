#include "includes/json.hpp"

namespace LightJson {
	Json::Json(const std::string& p_Name) {
		object.name = p_Name;
	}

	Json::~Json() {

	}
}