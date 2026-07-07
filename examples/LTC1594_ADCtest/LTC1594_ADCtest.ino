//-----------------------------------------------------------------------------------------
// LTC1594_ADCtest.ino
//-----------------------------------------------------------------------------------------

// AVR - LTC1594
// 13  - CLK
// 12  - DOUT
// 11  - DIN
// 10  - CS

// ESP8266 - LTC1594
// D5 / GPIO14 - CLK
// D6 / GPIO12 - DOUT
// D7 / GPIO13 - DIN
// D8 / GPIO15 - CS

#include <LTC1594.h>

#define VREF 3.30

#if defined(ESP8266)
const uint8_t LTC1594_CS_PIN = 15; // GPIO15, labeled D8 on many ESP8266 boards.
#else
const uint8_t LTC1594_CS_PIN = 10;
#endif

LTC1594 adc(LTC1594_CS_PIN);
uint16_t adcValue[4] = {0};

void setup() {
  Serial.begin(9600);
  adc.begin();
}

void loop() {
  uint32_t t1 = micros();
  for (uint8_t i = 0; i < 4; i++) {
    adcValue[i] = adc.readChannel(i);
  }
  uint32_t t2 = micros();

  Serial.println(F("========== LTC1594 ADC test =========="));
  for (uint8_t i = 0; i < 4; i++) {
    float voltage = (adcValue[i] * VREF) / 4096.0;
    Serial.print(F("Ingang "));
    Serial.print(i);
    Serial.print(F(": "));
    Serial.print(voltage, 3);
    Serial.println(F(" V"));
  }

  Serial.print(F("Samples: "));
  Serial.println(4);
  Serial.print(F("Sampling time: "));
  Serial.print(static_cast<double>(t2 - t1) / 1000, 4);
  Serial.println(F(" ms"));
  Serial.println();

  delay(1000);
}
