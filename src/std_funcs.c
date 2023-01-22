#include <MKL25Z4.h>

#include "../inc/std_funcs.h"
#include "../inc/rgb.h"
#include "../inc/timers.h"

void delay(volatile unsigned int time_delay) {
	while ( time_delay--) {
	}
}

void porte29_digital_in(void) {
	/* Enable clock on PORTE */
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	/* GPIO module */
	PORTE->PCR[29] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[29] |= PORT_PCR_MUX(1);
	
	/* Inputs */
	PTD->PDDR &= ~MASK(29);
}

void porte29_analog_in(void) {
	/* Enable clock on PORTE, configure pin 29 to analog */
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	PORTE->PCR[29] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[29] |= PORT_PCR_MUX(0);
}

void flash_reset_cause(void)
{
	unsigned n;

	for (n = 0; n < 3; n++) {
		if (RCM->SRS0 & RCM_SRS0_WDOG_MASK) { /* WDT caused reset */
			rgb_led_on(RED);
		} else if (RCM->SRS0 & RCM_SRS0_PIN_MASK) { /* Pin reset */
			rgb_led_on(GREEN);
		} else {
			rgb_led_on(BLUE);
		}

		COP_WDT_service();
		delay(DELAY_500_MS);
		rgb_led_off(RED);
		rgb_led_off(GREEN);
		rgb_led_off(BLUE);
		COP_WDT_service();
		delay(DELAY_500_MS);
	}
}
