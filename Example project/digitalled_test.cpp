/*
 * digitalled_test.cpp
 *
 *  Created on: Apr 9, 2016
 *      Author: Remko welling
 *      		remko@rfsee.nl
 *
 *
 */

#include "../Libraries/digitalled_test.h"
#include <math.h>


digitalled_test::digitalled_test()
:
_messageDisplay(true),
_ticker(0),
_led(0),
_runningTest7(false),
_runningTest8(false),
_runningTest9(false),
_runningTest10(false),
_frequency(0.3),
_illumination(0),
_testState(TEST_0)

{
	display.PrintfLn("Digital-LED Unit-tests.");
	display.PrintfLn("=======================");
}

digitalled_test::~digitalled_test()
{
	// TODO Auto-generated destructor stub
}

void digitalled_test::Step(void)
{
	_testState++;
	_messageDisplay = true;
	display.PrintfLn("-");
}

void digitalled_test::Cycle(void)
{
	_ticker++;
	if (_ticker == 20)
	{
		_led++;
		_ticker = 0;
		_illumination--;
	}

	switch (_testState)
	{
	case TEST_0:
		if(_messageDisplay)
		{
			display.PrintfLn("Test 0: Initialized.");
			_messageDisplay = false;
		}
		break;

		// Test function SetAllColor() that uses function SetColor() and set all LEDs RED
	case TEST_1:
		if(_messageDisplay)
		{
			display.PrintfLn("Test 1: All LED: RED.");
			_messageDisplay = false;
		}
		APA101_test.setAllColor(255,0,0);
		break;

		// Test function SetAllColor() that uses function SetColor() and set all LEDs GREEN
	case TEST_2:
		if(_messageDisplay)
		{
			display.PrintfLn("Test 2: All LED: GREEN.");
			_messageDisplay = false;
		}
		APA101_test.setAllColor(0,255,0);
		break;

		// Test function SetAllColor() that uses function SetColor() and set all LEDs BLUE
	case TEST_3:
		if(_messageDisplay)
		{
			display.PrintfLn("Test 3: All LED: BLUE.");
			_messageDisplay = false;
		}
		APA101_test.setAllColor(0,0,255);
		break;

		// Test function SetAllRGB() that uses function SetRGB() and set all LEDs RED
	case TEST_4:
		if(_messageDisplay)
		{
			display.PrintfLn("Test 4: All LED: RED.");
			_messageDisplay = false;
		}
		APA101_test.setAllRGB(0xff0000);
		break;

		// Test function SetAllRGB() that uses function SetRGB() and set all LEDs GREEN
	case TEST_5:
		if(_messageDisplay)
		{
			display.PrintfLn("Test 5: All LED: GREEN.");
			_messageDisplay = false;
		}
		APA101_test.setAllRGB(0x00ff00);
		break;

		// Test function SetAllRGB() that uses function SetRGB() and set all LEDs BLUE
	case TEST_6:
		if(_messageDisplay)
		{
			display.PrintfLn("Test 6: All LED: BLUE.");
			_messageDisplay = false;
		}
		APA101_test.setAllRGB(0x0000ff);
		break;

		// Test function switch all individual LEDs sequential off
	case TEST_7:
		if(_messageDisplay)
		{
			display.PrintfLn("Test 7: Switch LEDs off.");
			_messageDisplay = false;
		}

		if (!_runningTest7)
		{
			_led = 0;
			_runningTest7 = true;
		}
		if(_led < APA101_test.getFrameSize())
		{
			APA101_test.setLedOff(_led);
		}
		break;

		// Test function switch all individual LEDs sequential on
	case TEST_8:
		if(_messageDisplay)
		{
			display.PrintfLn("Test 8: Switch LEDs on.");
			_messageDisplay = false;
		}
		if (!_runningTest8)
		{
			_led = 0;
			_runningTest8 = true;
		}
		if(_led < APA101_test.getFrameSize())
		{
			APA101_test.setLedOn(_led);
		}
		break;

		// Make rainbow
	case TEST_9:
		if(_messageDisplay)
		{
			display.PrintfLn("Test 9: Set rainbow.");
			_messageDisplay = false;
		}

		uint8_t red;
		uint8_t green;
		uint8_t blue;

		if (!_runningTest9)
		{
			_led = 0;
			_runningTest9 = true;
		}

		// http://krazydad.com/tutorials/makecolors.php
		red = sin(_frequency * _led + 0) * 127 + 128;
		green = sin(_frequency * _led + 2) * 127 + 128;
		blue = sin(_frequency * _led + 4) * 127 + 128;

		if(_led < APA101_test.getFrameSize())
		{
			APA101_test.setColor(_led, red, green, blue);
		}
		break;

		// Test illumination of LED using function setAllIllumination() that uses setLedIllumination();
	case TEST_10:
		if(_messageDisplay)
		{
			display.PrintfLn("Test 10: Dim LEDs to off.");
			_messageDisplay = false;
		}

		if (!_runningTest10)
		{
			_illumination = 31;
			_runningTest10 = true;
		}

		APA101_test.setAllIllumination(_illumination);

		if (_illumination == 0)
		{
			Step();
		}
		break;

		// Test forced update of leds.
	case TEST_11:
		if(_messageDisplay)
		{
			display.PrintfLn("Test 11: Forced LED update.");
			_messageDisplay = false;
		}
		APA101_test.update(true); // update frame when frame is modified (no forced update)
		break;

	case TEST_12:
		// Test update as frame buffer is not changed, no updates.
		if(_messageDisplay)
		{
			display.PrintfLn("Test 12: Normal LED update.");
			_messageDisplay = false;
		}
		_testState = _testState;
		break;

	default:
		if(_messageDisplay)
		{
			display.PrintfLn("Tests finished.");
			_messageDisplay = false;
		}

		APA101_test.setAllColor(0,0,0);
		APA101_test.setColor(59, 255,255,255);

		break;
	}

	APA101_test.update(false); ///< update frame when frame is modified (no forced update)
}
