/***************************************************
Simple example of reading the MCP3208 analog input channels and printing
them all out.

Author: Rodolfo Prieto Maldonado
License: Public Domain
****************************************************/

#include <MCP3208.h>

MCP3208 adc;

#define ADCCS   PB7

int count = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("MCP3208 simple test.");

  /// Hardware SPI (specify CS, use any available digital pin)
  /// Can use defaults if available, 
  /// ex: UNO (SS=10), Huzzah (SS=15), Feather 32u4 (SS=17) or M0 (SS=16)
  //adc.begin();
  
  /// Specifying the digital pin to use as cs
  adc.begin(ADCCS);  

  /// Software SPI (specify all, use any available digital)
  /// (sck, mosi, miso, cs);
  //adc.begin(13, 11, 12, 10);
}

void loop() {
  for (int chan=0; chan<8; chan++) {
    Serial.print(adc.readADC(chan)); Serial.print("\t");
  }

  Serial.print("["); Serial.print(count); Serial.println("]");
  count++;
  
  delay(1000);
}
