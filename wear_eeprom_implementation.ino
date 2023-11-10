#include <EEPROM.h>

const int EEPROM_SIZE = 4096; // Adjust based on your EEPROM size

// Data Structure 1: Number and String
struct DataStruct1 {
  int number;
  char text[20]; // Assuming a maximum of 19 characters for the string
};

// Data Structure 2: Number, String, String, Bool, Float
struct DataStruct2 {
  int number;
  char text1[20];
  char text2[20];
  bool flag;
  float value;
};

void writeData(int address, const void *data, int dataSize) {
  for (int i = 0; i < dataSize; ++i) {
    EEPROM.write(address + i, *((uint8_t *)data + i));
  }
  EEPROM.commit();
}

void readData(int address, void *data, int dataSize) {
  for (int i = 0; i < dataSize; ++i) {
    *((uint8_t *)data + i) = EEPROM.read(address + i);
  }
}

void wearLevelWrite(const void *data, int dataSize) {
  int address = 0;
  int value = 0;

  // Find the address with the lowest value
  for (int i = 0; i < EEPROM_SIZE; i += dataSize) {
    int currentValue = EEPROM.read(i);
    if (currentValue < value || i == 0) {
      value = currentValue;
      address = i;
    }
  }

  // Write data to the address with the lowest value
  writeData(address, data, dataSize);
}

void printData(const void *data, int dataSize) {
  for (int i = 0; i < dataSize; ++i) {
    Serial.print(*((char *)data + i));
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);

  // Initialize EEPROM
  EEPROM.begin(EEPROM_SIZE);

  // Example Data Structure 1: Number and String
  DataStruct1 myData1;
  myData1.number = 42;
  strncpy(myData1.text, "Hello, ESP32!", sizeof(myData1.text));

  // Example wear-leveling writes for Data Structure 1
  wearLevelWrite(&myData1, sizeof(myData1));

  // Print data from EEPROM for Data Structure 1
  Serial.println("Data stored in EEPROM (Data Structure 1):");
  printData(&myData1, sizeof(myData1));

  // Example Data Structure 2: Number, String, String, Bool, Float
  DataStruct2 myData2;
  myData2.number = 99;
  strncpy(myData2.text1, "Text1", sizeof(myData2.text1));
  strncpy(myData2.text2, "Text2", sizeof(myData2.text2));
  myData2.flag = true;
  myData2.value = 3.14;

  // Example wear-leveling writes for Data Structure 2
  wearLevelWrite(&myData2, sizeof(myData2));

  // Print data from EEPROM for Data Structure 2
  Serial.println("Data stored in EEPROM (Data Structure 2):");
  printData(&myData2, sizeof(myData2));
}

void loop() {
  // Your code here
}
