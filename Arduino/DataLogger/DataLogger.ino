#include <SPI.h>
#include "Adafruit_MAX31855.h"
#include <MCP3208.h>

// RS485 control pin
#define RE_DE_PIN PA11
HardwareSerial Serial1(PA10, PA9);  // RS485 communication pins

// Constants for the message structure
#define START_MARKER 0x7E
#define SENSOR_TYPE_THERMOCOUPLE 0x01
#define SENSOR_TYPE_ADC 0x02

// Base class for sensors
class Sensor {
protected:
  uint8_t sensorType;
  uint8_t sensorID;

public:
  Sensor(uint8_t type, uint8_t id) : sensorType(type), sensorID(id) {}

  virtual void init() = 0;
  virtual void readAndSendData() = 0;

  void send_message(uint8_t *payload, uint8_t length) {
    uint8_t message[length + 5];
    uint8_t checksum = 0;

    message[0] = START_MARKER;
    message[1] = length;
    message[2] = sensorType;
    message[3] = sensorID;

    for (uint8_t i = 0; i < length; i++) {
      message[4 + i] = payload[i];
      checksum ^= payload[i];  // XOR checksum
    }

    message[length + 4] = checksum;

    digitalWrite(RE_DE_PIN, HIGH);  // Enable transmission mode
    Serial1.write(message, length + 5);  // Transmit message
    digitalWrite(RE_DE_PIN, LOW);   // Return to reception mode

    // For debugging: print the message
    printFormattedMessage(message, length + 5);
    delay(1000);
  }

  void printFormattedMessage(uint8_t* message, uint8_t messageLength) {
    Serial.println("Message Sent:");
    Serial.print("  Start Marker: 0x"); Serial.println(message[0], HEX);
    Serial.print("  Length: "); Serial.println(message[1]);
    Serial.print("  Sensor Type: "); Serial.println(sensorType == SENSOR_TYPE_THERMOCOUPLE ? "Thermocouple" : "ADC");
    Serial.print("  Sensor ID: "); Serial.println(sensorID);
    Serial.print("  Payload: ");
    for (int i = 4; i < messageLength - 1; i++) {
      Serial.print((char)message[i]);
    }
    Serial.println();
    Serial.print("  Checksum: 0x"); Serial.println(message[messageLength - 1], HEX);
    Serial.println();
  }
};

// Thermocouple sensor class
class Thermocouple : public Sensor {
private:
  Adafruit_MAX31855 thermocouple;

public:
  Thermocouple(uint8_t id, uint8_t csPin)
    : Sensor(SENSOR_TYPE_THERMOCOUPLE, id), thermocouple(csPin) {}

  void init() override {
    if (!thermocouple.begin()) {
      Serial.println("Thermocouple initialization failed!");
      while (1);
    }
    Serial.println("Thermocouple initialized.");
  }

  void readAndSendData() override {
    double tempCelsius = thermocouple.readCelsius();
    if (!isnan(tempCelsius)) {
      char payload[10];
      snprintf(payload, sizeof(payload), "%.4f", tempCelsius);
      uint8_t length = strlen(payload);
      send_message((uint8_t*)payload, length);
    }
  }
};

// ADC sensor class (multiple sensors on one ADC module)
class ADCSensor : public Sensor {
private:
  MCP3208& adc;  // Reference to the shared ADC instance
  uint8_t channel;

public:
  ADCSensor(uint8_t id, MCP3208& adcModule, uint8_t adcChannel)
    : Sensor(SENSOR_TYPE_ADC, id), adc(adcModule), channel(adcChannel) {}

  void init() override {
    // ADC initialization handled globally, no need to do anything here
  }

  void readAndSendData() override {
    int value = adc.readADC(channel);
    char payload[5];
    snprintf(payload, sizeof(payload), "%d", value);
    uint8_t length = strlen(payload);
    send_message((uint8_t*)payload, length);
  }
};

// RS485 Communication
void initRS485() {
  pinMode(RE_DE_PIN, OUTPUT);
  digitalWrite(RE_DE_PIN, LOW);  // Set to reception mode
  Serial1.begin(115200);  // RS485 communication
  Serial.println("RS485 initialized.");
}

// Global ADC instance
MCP3208 adc;

// Sensor instances
Thermocouple tc1(1, PB0);  // Thermocouple with ID 1
ADCSensor adcSensors[8] = {
  ADCSensor(2, adc, 0), ADCSensor(3, adc, 1), ADCSensor(4, adc, 2), 
  ADCSensor(5, adc, 3), ADCSensor(6, adc, 4), ADCSensor(7, adc, 5), 
  ADCSensor(8, adc, 6), ADCSensor(9, adc, 7)
};

void setup() {
  Serial.begin(115200);  // Debugging serial communication

  // Initialize RS485
  initRS485();

  // Initialize ADC
  adc.begin(PB7);  // Initialize MCP3208 ADC with CS pin

  // Initialize sensors
  tc1.init();
  for (int i = 0; i < 8; i++) {
    adcSensors[i].init();
  }
}

void loop() {
  // Read and transmit data from thermocouple
  tc1.readAndSendData();

  // Read and transmit data from all 8 ADC sensors
  for (int i = 0; i < 8; i++) {
    adcSensors[i].readAndSendData();
  }

  // Wait for 2 seconds before the next transmission
  delay(2000);
}
