#include "Includes/JsonReader.hpp"

using namespace LightJson;

int main() {
    JsonReader jsonReader = JsonReader();

    jsonReader.Open("Resources/JsonSample.json");
    jsonReader.Deserialize();
    jsonReader.Close();
}
