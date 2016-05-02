
/* Includes */

#include "main.h"

#define UNITTEST


/* Private macro */
/* Private variables */
/* Private function prototypes */

/* Private functions */

int main(void)
{

	/* TODO - Add your application code here */

	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);

	STM_EVAL_LEDOn(LED3);
	STM_EVAL_LEDOn(LED4);

#ifdef UNITTEST
	digitalled_test APA101_test;
	bool buttonMemory = false;
	bool button = false;
#endif

#ifndef UNITTEST
	digitalled APA101;

#endif

	int b = 0;

	/* Infinite loop */
	while (1)
	{

#ifdef UNITTEST

		// Periodically test BUTTON_USER
		b++;
		if (b == 50)
		{
			STM_EVAL_LEDToggle(LED3); // Toggle LED3
			b = 0;	// Reset b

			if (STM_EVAL_PBGetState(BUTTON_USER))
			{
				button = true;
			}
			else
			{
				button = false;
			}
		}

		// When BUTTON_USER pressed
		if (button && (button != buttonMemory))
		{
			STM_EVAL_LEDOn(LED4);
			APA101_test.Step();
		}
		else
		{
			STM_EVAL_LEDOff(LED4);
		}
		buttonMemory = button;

		APA101_test.Cycle();
#endif



		/// Normal code for execution
#ifndef UNITTEST

		/// Toggle LED3
		b++;
		if (b == 100)
		{
			STM_EVAL_LEDToggle(LED3);
			b = 0;
		}

		if (STM_EVAL_PBGetState(BUTTON_USER))
		{
			STM_EVAL_LEDOn(LED4);
			APA101.setAllColor(2,4,8);
		}
		else
		{
			STM_EVAL_LEDOff(LED4);
			APA101.setAllColor(255,0,0);
		}

		APA101.update(false);
#endif

	}
}


/*
 * Callback used by stm324xg_eval_i2c_ee.c.
 * Refer to stm324xg_eval_i2c_ee.h for more info.
 */
extern "C" uint32_t sEE_TIMEOUT_UserCallback(void)
{
	/* TODO, implement your code here */
	while (1)
	{
	}
}

