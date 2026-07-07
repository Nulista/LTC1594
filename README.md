# LTC1594

Arduino library for the LTC1594 4-channel 12-bit ADC.

This library was originally based on work by Souvik Saha and was adapted by Ludo Nulens for the LTC1594.

## Features

- Reads channels 0 to 3 from an LTC1594 ADC.
- Uses the Arduino SPI library.
- Limits SPI transactions to 200 kHz, matching the LTC1594 datasheet maximum serial clock.
- Includes examples for a serial monitor test and an ESP8266 Nokia 5110 display test.

## Wiring

### AVR / Arduino Uno

| Arduino | LTC1594 |
| --- | --- |
| 13 | CLK |
| 12 | DOUT |
| 11 | DIN |
| 10 | CS |

### ESP8266

| ESP8266 | LTC1594 |
| --- | --- |
| D5 / GPIO14 | CLK |
| D6 / GPIO12 | DOUT |
| D7 / GPIO13 | DIN |
| D8 / GPIO15 | CS |

The LTC1594 is a 5 V device. When using a 3.3 V controller such as the ESP8266, make sure all signal levels are compatible with your hardware. Use level shifting where needed.

## Basic usage

```cpp
#include <LTC1594.h>

#if defined(ESP8266)
LTC1594 adc(15); // GPIO15, labeled D8 on many ESP8266 boards.
#else
LTC1594 adc(10);
#endif

void setup() {
  Serial.begin(9600);
  adc.begin();
}

void loop() {
  uint16_t value = adc.readChannel(0);
  Serial.println(value);
  delay(1000);
}
```

`readChannel(channel)` accepts channels `0` to `3` and returns a 12-bit value from `0` to `4095`.

## Reference voltage

To convert an ADC reading to voltage:

```cpp
float voltage = (reading * VREF) / 4096.0;
```

Set `VREF` to the reference voltage used by your circuit.
