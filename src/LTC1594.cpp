//Release Date: 15-12-2018
//souvikssaha@gmail.com
// Aangepast voor LTC1594 op 21-01-2022 door Ludo Nulens
/*===========================================================================
DAC7611 device library code is placed under the MIT license
Copyright (c) 2018 Souvik Saha

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
===========================================================================*/
/* Volgens de datasheet:
Maximum serial clock speed is 200kHz, which corresponds to a
10.5kHz sampling rate.
*/

#include "LTC1594.h"
#include "Arduino.h"
#include "SPI.h"

LTC1594::LTC1594(int CS){
	chipSel = CS;
}

void LTC1594::begin(void)
{
	pinMode(chipSel, OUTPUT);
	digitalWrite(chipSel, HIGH);
	SPI.begin();
}

uint16_t LTC1594::readChannel(byte thisCh)
{
	uint16_t dataIn = 0;
	uint16_t result = 0;

	if (thisCh > 3) thisCh = 0;
	uint8_t dataOut = 8 + thisCh;

	SPI.beginTransaction(SPISettings(200000, MSBFIRST, SPI_MODE0));
	digitalWrite(chipSel, LOW);
	dataIn = SPI.transfer(dataOut);
	result = dataIn & 0x1F;
	dataIn = SPI.transfer(0x00);
	result = result << 8;
	result = (result | dataIn) >> 1;
	digitalWrite(chipSel, HIGH);
	SPI.endTransaction();

	return result;
}
