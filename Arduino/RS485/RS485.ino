// RS485 connections
#define TX_EN_PIN PA11 // RE and DE pin connected to RS485 module for controlling transmission and reception
//                      RX    TX
HardwareSerial rs485(PA10, PA9);


#define START_MARKER 0x7E


void setup() {
  pinMode(TX_EN_PIN, OUTPUT);
  digitalWrite(TX_EN_PIN, LOW);
  
  rs485.begin(115200); // Set baud rate for RS485 communication
}

void send_message(uint8_t sensor_type, uint8_t sensor_id, uint8_t *payload, uint8_t length) {
  uint8_t message[length + 5];
  uint8_t checksum = 0;

  message[0] = START_MARKER;
  message[1] = length;
  message[2] = sensor_type;
  message[3] = sensor_id;

  for (uint8_t i = 0; i < length; i++) {
    message[4 + i] = payload[i];
    checksum ^= payload[i];
  }

  message[length + 4] = checksum;

  digitalWrite(TX_EN_PIN, HIGH); // Enable RS485 Transmitter
  rs485.write(message, length + 5); // Transmit message
  digitalWrite(TX_EN_PIN, LOW); // Disable RS485 Transmitter
}

void loop() {
  // Example call Thermocouple1 T1 value 25.3662
  uint8_t sensor_type = 'T';
  uint8_t sensor_id = 1;
  float sensor_value = 25.3662;
  char payload[10];

  snprintf(payload, sizeof(payload), "%.4f", sensor_value);
  uint8_t length = strlen(payload);

  send_message(sensor_type, sensor_id, (uint8_t *)payload, length);

  delay(1000); // Delay 1 second between messages
}
