/*
 MIT License

 Copyright (c) 2020 Pieter Bloemendaal (https://github.com/pieterbl)

 Project Grove_LCD_RGB_Clock
 (https://github.com/pieterbl/Grove_LCD_RGB_Clock)

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
 */

#include <Arduino.h>
#include <Grove_LCD_RGB_Backlight_Extension.hpp>
#include <Grove_RTC_DS1307_Extension.hpp>
#include <Grove_RTC_DS1307_TimeLibSyncProvider.hpp>
#include <Time_Extension.hpp>

// set up the LCD's number of columns and rows
GroveLcdRgbBacklight rgbLcd(16, 2);
ColorSlider lcdSlider(Colors::Orange, Colors::Magenta);

// define DS1307 RTC clock
GroveRtcDs1307 ds1307Clock;

// define Time_Extension wrapper for DS1307 RTC clock
TimeExtension timeObj;

void setup() {

	Serial.begin(9600);

	// begin DS1307 real-time-clock
	ds1307Clock.begin();

	// synchronize Time library with DS1307 real-time-clock
	GroveRtcDs1307TimeLibSyncProvider::initialize(&ds1307Clock);

	rgbLcd.initialize();
}

// returns values from 0-3
uint8_t getCol() {

	time_t nowTime = timeObj.getNow();
	tmElements_t timeLibTimeStruct;

	// TimeLib::breakTime
	::breakTime(nowTime, timeLibTimeStruct);

	uint8_t col = timeLibTimeStruct.Second / 15;
	return col;
}

void printOnLine(uint8_t col, uint8_t row, const String &text) {
	rgbLcd.setCursor(0, row);
	rgbLcd.print("   "); // erase first columns, for when moving to the right
	rgbLcd.setCursor(col, row);
	rgbLcd.print(text);
	rgbLcd.print("   "); // erase last columns, for when moving to the left
}

void loop() {

	uint8_t col = getCol();
	printOnLine(col, 0, timeObj.getDateString());
	printOnLine(col, 1, timeObj.getTimeString());

	Serial.print("TimeLib: ");
	Serial.println(timeObj.getDateTimeString());
	Serial.print("Column: ");
	Serial.println(col);
	Serial.println();

	// wait 300 ms until we continue (above) with printing date/time.
	// during the wait, we continue to "color-slide" every 50 ms.
	lcdSlider.delayAndSlide(rgbLcd, 300, 50);
}

