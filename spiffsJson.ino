#include <ArduinoJson.h>
#include <SPIFFS.h>

struct DataStruct {
  int number;
  char text[20]; // Assuming a maximum of 19 characters for the string
};

const char *filename = "/data.json";

void saveData(const DataStruct &data) {
  File file = SPIFFS.open(filename, "w");
  if (file) {
    // Create a JSON document
    DynamicJsonDocument doc(1024); // Adjust the size as needed

    // Populate the JSON document
    doc["number"] = data.number;
    doc["text"] = data.text;

    // Serialize the JSON document to the file
    serializeJson(doc, file);

    file.close();
  } else {
    Serial.println("Failed to open file for writing");
  }
}

void readData(DataStruct &data) {
  File file = SPIFFS.open(filename, "r");
  if (file) {
    // Create a JSON document
    DynamicJsonDocument doc(1024); // Adjust the size as needed

    // Parse the JSON document from the file
    DeserializationError error = deserializeJson(doc, file);
    if (!error) {
      // Extract data from the JSON document
      data.number = doc["number"];
      strncpy(data.text, doc["text"] | "", sizeof(data.text));
    } else {
      Serial.println("Failed to parse JSON");
    }

    file.close();
  } else {
    Serial.println("Failed to open file for reading");
  }
}

// Other CRUD functions can be similarly adapted

void setup() {
  Serial.begin(115200);

  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS initialization failed!");
    return;
  }

  // Example data
  DataStruct myData;
  myData.number = 42;
  strncpy(myData.text, "Hello, ESP32!", sizeof(myData.text));

  // Save data to SPIFFS in JSON format
  saveData(myData);

  // Read and print data from SPIFFS in JSON format
  DataStruct retrievedData;
  readData(retrievedData);
  Serial.println("Retrieved data in JSON format:");
  Serial.println(retrievedData.number);
  Serial.println(retrievedData.text);

  // Other CRUD operations can be added as needed
}

void loop() {
  // Your code here
}
