#include "includes/light_json_reader.hpp"
#include "includes/light_json_writer.hpp"

int main() {
	LightJson::JsonWriter jsonWriter;

	jsonWriter.Create("test.json");
	jsonWriter.Open();

	jsonWriter.Close();

	LightJson::JsonReader jsonReader;

}