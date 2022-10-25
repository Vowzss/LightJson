#include <string>
#include <fstream>

namespace LightJson {
	struct JsonObject {
		std::string name;
		std::ofstream file;
	};

	class Json
	{
	public:
		Json(const std::string& p_Name);
		~Json();

		JsonObject object;
	private:
	};
}