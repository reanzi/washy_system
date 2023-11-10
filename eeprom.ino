#include <EEPROM.h>

struct DataStruct {
  int number;
  char text[20]; // Assuming a maximum of 19 characters for the string
};

void saveData(const DataStruct &data, int address) {
  EEPROM.put(address, data);
  EEPROM.commit(); // This is necessary to save changes to EEPROM
}

void readData(DataStruct &data, int address) {
  EEPROM.get(address, data);
}

void updateData(const DataStruct &data, int address) {
  saveData(data, address);
}

void deleteData(int address) {
  DataStruct emptyData = {0, ""}; // Default values for deletion
  saveData(emptyData, address);
}

void printData(const DataStruct &data) {
  Serial.print("Number: ");
  Serial.println(data.number);
  Serial.print("Text: ");
  Serial.println(data.text);
  Serial.println("-------------");
}

void setup() {
  Serial.begin(115200);
  
  // Initialize EEPROM with the size of your data structure
  EEPROM.begin(sizeof(DataStruct));

  // Example data
  DataStruct myData;
  myData.number = 42;
  strncpy(myData.text, "Hello, ESP32!", sizeof(myData.text));

  // Save data to EEPROM
  saveData(myData, 0);

  // Read and print data from EEPROM
  DataStruct retrievedData;
  readData(retrievedData, 0);
  printData(retrievedData);

  // Update data in EEPROM
  DataStruct updatedData = {99, "Updated Text"};
  updateData(updatedData, 0);

  // Read and print updated data from EEPROM
  readData(retrievedData, 0);
  printData(retrievedData);

  // Delete data in EEPROM
  deleteData(0);

  // Read and print deleted data from EEPROM
  readData(retrievedData, 0);
  printData(retrievedData);
}

void loop() {
  // Your code here
}
