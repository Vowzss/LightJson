#include "includes/light_json_reader.hpp"
#include "includes/light_json_writer.hpp"

int main() {
	LightJson::JsonWriter testJsonWriter;

	testJsonWriter.Create("test.json");
	testJsonWriter.Open("test.json");
	testJsonWriter.Close("test.json");
	testJsonWriter.Delete();

	testJsonWriter.Create("ez.json");
	testJsonWriter.Open();
	testJsonWriter.Close();
	testJsonWriter.Delete();

	LightJson::JsonReader jsonReader;

}