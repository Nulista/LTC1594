//-----------------------------------------------------------------------------------------
// LTC1594_ADCtest.ino: 21/01/2022 door Ludo Nulens.............
//-----------------------------------------------------------------------------------------

// AVR  -   LTC1594
//  13  -    CLK
//  12  -    DOUT
//  11  -    DIN
//  10  -    CS --> CSMUX and CSADC samen verbonden

// ESP8266 - LTC1594
// D5   -    CLK
// D6   -    DOUT
// D7   -    DIN
// D8   -    CS --> CSMUX and CSADC samen verbonden

/**
* Deze code meet de ingangspanning op de 4 ingangen en display op Nokia5110 via i2c
* Code wordt uitgevoerd op ESP8266 met 3.3V
*/
//-----------------------------------------------------------------------------------------

#include <Adafruit_GFX.h>
#include <PCF8574_PCD8544.h>
#include <U8g2_for_Adafruit_GFX.h>

#include <LTC1594.h>

PCF8574_PCD8544 display = PCF8574_PCD8544(0x20, 3, 7, 6, 5, 4);
U8G2_FOR_ADAFRUIT_GFX u8g2;

#define Vref 3.30 			//change according to your Vref value.

LTC1594 adc = LTC1594(D8); 	//Parameter passed is the CS pin number. Change according to requirement.

int 	ADC_ch[4] = {0};

uint32_t t1;

void setup() {
	
	Serial.begin(9600);
	adc.begin();
	
	display.begin();
	display.setContrast(57);              // Adjust for your display
	u8g2.begin(display);                 // connect u8g2 procedures to Adafruit GFX

	display.clearDisplay();
	display.setTextColor(BLACK);
	u8g2.setFont(u8g2_font_squirrel_tr);
	u8g2.setCursor(3, 15);
	u8g2.println("-- Nulista --");
	u8g2.setCursor(0, 35);
	u8g2.println("LTC1594 ADC");
	display.display();
	
	delay(4000);
	display.clearDisplay();
}

void loop() {	
	
	if(millis() - t1 > 1000){    // enkel om de seconde een meting
		t1 = millis();
		for(int i=0; i<4; i++){
			ADC_ch[i] = adc.readChannel(i);
		}
		ADC_ch[1] = ADC_ch[1]*10; // omdat ingang 2 en 10 weerstand divider heeft
		display.clearDisplay();
		u8g2.setFont(u8g2_font_6x10_mf);
		u8g2.setCursor(3, 7);
		u8g2.print("- Voltmeter -");
		display.drawLine(0, 8, 83, 8, BLACK); 
		for(int i=0; i<4; i++){
			u8g2.setCursor(0, (i*8)+20);
			float Volt = (ADC_ch[i]*Vref)/4096.0;
			Volt = roundf(Volt*100)/100;  // We ronden af tot op 2 cijders na de komma
			if (Volt >9.99) u8g2.printf ("In %d: %2.2f V",i,Volt); // PS printf is niet beschikbaar bij AVR processoren
			else u8g2.printf ("In %d:  %2.2f V",i,Volt); // PS printf is niet beschikbaar bij AVR processoren
		}
		display.display();
	}

}
