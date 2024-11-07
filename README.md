# JoeTheDatalogger

A high-performance real-time Data Acquisition and Logging unit designed specifically for High Powered Rockets. The system provides robust sensor data collection, real-time transmission capabilities, and redundant data storage options.

## Features

### Sensor Integration
- **Thermocouple Sensing**: Uses MAX31855 for high-accuracy temperature measurements
  - Temperature range: -200°C to +1350°C
  - Resolution: 0.25°C
  - Built-in cold-junction compensation
  - Fault detection for sensor issues

- **Pressure Sensing**: Implements MCP3204 12-bit ADC for pressure transducer readings
  - 4 single-ended input channels
  - Resolution: 12-bit (4096 steps)
  - Reference voltage: 5V
  - Sampling rate: Up to 100 ksps

### Real-time Communication
- **RS485 Interface**
  - 2-wire half-duplex communication
  - Protocol: Custom "chYappy v1" packet format
  - Baud rate: 115200
  - Packet structure:
    ```
    | Start (1B) | Length (1B) | Type (1B) | ID (1B) | Payload (NB) | Checksum (1B) |
    ```
  [Chyappy]("https://github.com/AryanRai/chyappy")

- **LoRa SX1278**
  - Long-range wireless communication
  - Frequency: 433MHz
  - Spreading Factor: 7-12 (configurable)
  - Bandwidth: 125kHz
  - Coding Rate: 4/5
  - Maximum Range: ~10km (line of sight)
  - Transmit Power: up to +20dBm

### Inertial Measurement
- **MPU6050 6-DOF IMU**
  - 3-axis accelerometer
    - Range: ±2g, ±4g, ±8g, ±16g
    - 16-bit resolution
  - 3-axis gyroscope
    - Range: ±250, ±500, ±1000, ±2000°/s
    - 16-bit resolution
  - Digital Motion Processor (DMP)
  - Temperature sensor
  - I2C interface
  - Update rate: up to 1kHz

### Data Storage
- **NAND Flash** (Coming soon)
  - High-speed local storage
  - Capacity: TBD

- **SD Card** (Coming soon)
  - Removable storage option
  - Supports standard SD cards

## Hardware

### Core System
- MCU: STM32L4 series
- Operating voltage: 3.3V
- Clock speed: 32 MHz

### Pin Assignments

#### SPI1 (Sensors)
- MOSI: PA7
- MISO: PA6 
- SCK: PA5
- TC_CS: PB0 (Thermocouple chip select)
- ADC_CS: PA12 (ADC chip select)

#### UART (Communications)
- UART1: RS485 interface
  - TX: PA9
  - RX: PA10
  - TX_EN: PA11 (RS485 direction control)
- UART2: Debug interface
  - TX: PA2
  - RX: PA3

## Software Architecture

### Sensor Handling
- Independent enable/disable control for each sensor
- Automatic fault detection and reporting
- Configurable sampling rates

### Data Protocol
The RS485 communication uses a custom packet protocol (chYappy v1):
- Start marker: 0x7E
- Sensor types:
  - 'T': Temperature data
  - 'A': ADC/Pressure data
- Checksum: XOR of payload bytes

### Status Monitoring
- Thermocouple status codes:
  - 0: Not active
  - 1: Active and operational
  - 2: Error state
- ADC status codes:
  - 0: Not active
  - 1: Active and operational
  - 2: Error state

## Getting Started

1. Clone the repository
2. Open the project in STM32CubeIDE
3. Configure sensor enables in main.c:
   ```c
   int tc_en_bool = 1;  // Enable thermocouple
   int adc_en_bool = 1; // Enable ADC
   int rs_en_bool = 1;  // Enable RS485
   ```
4. Build and flash to your STM32L4 device

## Testing & Flight Computer Conversion

### Hardware Testing Requirements
- **MPU6050 IMU Testing**
  - Accelerometer calibration and testing
    - Zero-g offset calibration
    - Scale factor verification
    - Cross-axis alignment
  - Gyroscope calibration and testing
    - Zero-rate offset calibration
    - Sensitivity verification
    - Angular random walk measurement
  - Temperature compensation testing
  - DMP functionality verification
  - Sensor fusion accuracy testing

- **LoRa SX1278 Testing**
  - Range testing at different spreading factors
  - Interference resistance verification
  - Power consumption measurement
  - Link quality assessment
  - Packet loss rate testing
  - Maximum throughput testing

### Flight Computer Features
- [x] Integrate MPU6050 6-DOF IMU
- [x] LoRa telemetry implementation



## Future Enhancements
- [ ] LoRa wireless integration
- [ ] NAND Flash storage implementation
- [ ] SD Card support
- [ ] IMU
- [ ] Convert to Flight Computer

## License
This project is licensed under the MIT License - see the LICENSE file for details.

## Contributing
Contributions are welcome! Please feel free to submit a Pull Request.
