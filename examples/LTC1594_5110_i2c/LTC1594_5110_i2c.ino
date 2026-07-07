//-----------------------------------------------------------------------------------------
// LTC1594_5110_i2c.ino
//-----------------------------------------------------------------------------------------

// ESP8266 - LTC1594
// D5 - CLK
// D6 - DOUT
// D7 - DIN
// D8 - CS

#include <Adafruit_GFX.h>
#include <PCF8574_PCD8544.h>
#include <U8g2_for_Adafruit_GFX.h>
#include <LTC1594.h>

#define VREF 3.30

const uint8_t LTC1594_CS_PIN = D8;

PCF8574_PCD8544 display = PCF8574_PCD8544(0x20, 3, 7, 6, 5, 4);
U8G2_FOR_ADAFRUIT_GFX u8g2;
LTC1594 adc(LTC1594_CS_PIN);

uint16_t adcValue[4] = {0};
uint32_t lastMeasurement = 0;

void setup() {
  Serial.begin(9600);
  adc.begin();

  display.begin();
  display.setContrast(57);
  u8g2.begin(display);
  delay(600);

  display.clearDisplay();
  display.setTextColor(BLACK);
  u8g2.setFont(u8g2_font_crox1hb_tr);
  u8g2.setCursor(8, 15);
  u8g2.println("-- Nulista --");
  u8g2.setCursor(0, 35);
  u8g2.println("LTC1594 ADC");
  display.display();

  delay(3700);
  display.clearDisplay();
}

void loop() {
  if (millis() - lastMeasurement > 1000) {
    lastMeasurement = millis();

    for (uint8_t i = 0; i < 4; i++) {
      adcValue[i] = adc.readChannel(i);
    }

    adcValue[1] = adcValue[1] * 10; // Ingang 1 gebruikt een 1:10 spanningsdeler.

    display.clearDisplay();
    u8g2.setFont(u8g2_font_pressstart2p_8f);
    u8g2.setCursor(0, 8);
    u8g2.print(" Voltmeter");
    u8g2.setFont(u8g2_font_mozart_nbp_tf);
    display.drawLine(0, 8, 83, 8, BLACK);

    for (uint8_t i = 0; i < 4; i++) {
      float voltage = (adcValue[i] * VREF) / 4096.0;
      voltage = roundf(voltage * 100) / 100;
      u8g2.setCursor(0, (i * 8) + 20);
      if (voltage > 9.99) {
        u8g2.printf("In %d:%2.2f V", i, voltage);
      } else {
        u8g2.printf("In %d: %2.2f V", i, voltage);
      }
    }

    display.display();
  }
}
