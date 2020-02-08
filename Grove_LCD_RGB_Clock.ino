/*
 MIT License

 Copyright (c) 2020 Pieter Bloemendaal (https://github.com/pieterbl)

 Project Grove\_LCD\_RGB\_Clock
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
#include "Grove_LCD_RGB_Backlight_Extension.hpp"
#include "Grove_RTC_DS1307_Extension.hpp"

// set up the LCD's number of columns and rows
GroveLcdRgbBacklight rgbLcd(16, 2);
ColorSlider lcdSlider(Colors::Orange, Colors::Magenta);

// define clock
GroveRtcDs1307 clock;

void setup() {

	rgbLcd.initialize();

	// Sunday, 2020-FEB-02 14:30:00
	clock.begin();
	clock.initializeDayOfWeekYMDHMS(SUN, 2020, 2, 2, 14, 30, 0);
}

void loop() {

	rgbLcd.setCursor(0, 0);
	rgbLcd.print(clock.getDateString());

	rgbLcd.setCursor(0, 1);
	rgbLcd.print(clock.getTimeString());

	// wait 300 ms until we continue (above) with printing date/time.
	// during the wait, we continue to "color-slide" every 50 ms.
	lcdSlider.delayAndSlide(rgbLcd, 300, 50);
}

