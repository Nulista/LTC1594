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
* Deze code meet de ingangspanning op de 4 ingangen en stuurt ze serieel uit
* Meet ook de sampeltijd voor deze 4 metingen
* en draait op een esp8266 met 3.3V (moet eigenlijk 5V zijn volgens datasheet
* Volgens internet is de ESP8266 5V tollerant op de ingangen met een VCC 3.3V
* Sample time for  4 metingen = ±0.622ms of ±0.155ms voor 1 meting op spi freq   200.000Khz
* Sample time for  4 metingen = ±0.041ms of ±0.166ms voor 1 meting op spi freq 1.000.000Khz
*/
//-----------------------------------------------------------------------------------------
#include <LTC1594.h>
#define Vref 3.30 			//change according to your Vref value.

LTC1594 adc = LTC1594(D8); 	//Parameter passed is the CS pin number. Change according to requirement.

int 	ADC_ch[4] = {0};
double	Volt[4] = {0};

void setup() {
	adc.begin();
	Serial.begin(9600);
}

void loop() {		
	uint32_t t1;
	uint32_t t2;	
	//----
	t1 = micros();
	for(int i=0; i<4; i++){
		ADC_ch[i] = adc.readChannel(i);
	}
	t2 = micros();
	Serial.println("========== Nulista software =================>");
	for(int i=0; i<4; i++){
		Serial.printf ("Ingang %d: %2.3f V \n",i,(ADC_ch[i]*Vref)/4096.0); // PS printf is niet beschikbaar bij AVR processoren
		//Serial.println((ADC_ch[i]*Vref)/4096.0);
	}
	// sampling time
	Serial.print("Samples: ");
	Serial.println(4);
	Serial.print("Sampling time: ");
	Serial.print(static_cast<double>(t2 - t1) / 1000, 4);
	Serial.println("ms"); 
	//----- 
	delay(1000);
}
