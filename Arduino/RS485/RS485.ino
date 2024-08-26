// RS485 connections
#define RE_DE_PIN PA11 // RE and DE pin connected to RS485 module for controlling transmission and reception
//                      RX    TX
HardwareSerial Serial1(PA10, PA9);

void setup() {
  pinMode(RE_DE_PIN, OUTPUT);
  digitalWrite(RE_DE_PIN, LOW); // Set to receive mode

  // Initialize hardware serial with the baud rate of 9600 (match with receiver)
  Serial.begin(115200);      // For debugging via USB Serial Monitor
  Serial1.begin(115200);     // RS485 communication using Serial1 (TX1 and RX1 on hardware serial)
}

void loop() {
  // Sample data to send
  int sensorValue = analogRead(A0); // Example of reading a sensor value
  float temperature = 23.5;         // Example of temperature data
  int statusFlag = 1;               // Example of a status flag

  // Convert data to string for transmission
  String payload = String(sensorValue) + "," + String(temperature) + "," + String(statusFlag);

  // Switch to transmission mode
  digitalWrite(RE_DE_PIN, HIGH);  // Enable transmission

  // Send data via RS485 using Serial1
  Serial1.println(payload);

  // Debugging output
  Serial.println("Data sent: " + payload);

  // Switch back to reception mode
  digitalWrite(RE_DE_PIN, LOW);   // Enable reception
  
  delay(1000); // Wait before sending the next packet
}
