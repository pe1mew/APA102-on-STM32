/*
 * digitalled_test.h
 *
 *  Created on: Apr 9, 2016
 *      Author: Remko welling
 *      		remko@rfsee.nl
 *
 *	\version 0.8	Initial release for the HACOX project team for code review
 *	\version 0.9	modifications to test new feature of version 0.9.
 *
 */

#ifndef DIGITALLED_TEST_H_
#define DIGITALLED_TEST_H_

#include <stdint.h>

#include "../Libraries/digitalled.h"


class digitalled_test
{
public:
	digitalled_test();
	virtual ~digitalled_test();

	void Step(void);
	void Cycle(void);

private:
	digitalled 	APA101_test;
	touchdisplay display;

	bool		_messageDisplay;
	uint32_t 	_ticker;
	int 		_led;
	bool 		_runningTest7;
	bool 		_runningTest8;
	bool		_runningTest9;
	bool		_runningTest10;
	float 		_frequency;
	uint8_t		_illumination;

	enum states
	{
		TEST_0 = 0,
		TEST_1,
		TEST_2,
		TEST_3,
		TEST_4,
		TEST_5,
		TEST_6,
		TEST_7,
		TEST_8,
		TEST_9,
		TEST_10,
		TEST_11,
		TEST_12
	};

	uint8_t _testState;
};

#endif /* DIGITALLED_TEST_H_ */
