#include <MKL25Z4.h>
#include "rgb.h"
#include "std_funcs.h"

#ifdef FAST_ACCESS
static void _red_on(void) {
	FPTB->PCOR = MASK(RED_SHIFT);
}

static void _green_on(void) {
	FPTB->PCOR = MASK(GREEN_SHIFT);
}

static void _blue_on(void) {
	FPTD->PCOR = MASK(BLUE_SHIFT);
}

static void _red_off(void) {
	FPTB->PSOR = MASK(RED_SHIFT);
}

static void _green_off(void) {
	FPTB->PSOR = MASK(GREEN_SHIFT);
}

static void _blue_off(void) {
	FPTD->PSOR = MASK(BLUE_SHIFT);
}

static void _red_toggle(void) {
	FPTB->PTOR = MASK(RED_SHIFT);
}

static void _green_toggle(void) {
	FPTB->PTOR = MASK(GREEN_SHIFT);
}

static void _blue_toggle(void) {
	FPTD->PTOR = MASK(BLUE_SHIFT);
}

#else
static void _red_on(void) {
	PTB->PCOR = MASK(RED_SHIFT);
}

static void _green_on(void) {
	PTB->PCOR = MASK(GREEN_SHIFT);
}

static void _blue_on(void) {
	PTD->PCOR = MASK(BLUE_SHIFT);
}

static void _red_off(void) {
	PTB->PSOR = MASK(RED_SHIFT);
}

static void _green_off(void) {
	PTB->PSOR = MASK(GREEN_SHIFT);
}

static void _blue_off(void) {
	PTB->PSOR = MASK(BLUE_SHIFT);
}

static void _red_toggle(void) {
	PTB->PTOR = MASK(RED_SHIFT);
}

static void _green_toggle(void) {
	PTB->PTOR = MASK(GREEN_SHIFT);
}

static void _blue_toggle(void) {
	PTB->PTOR = MASK(BLUE_SHIFT);
}

#endif /* FAST ACCESS */

void rgb_init(bool display) {
	/* Enable clock on PORTB and PORTD */
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;
	
	/* Configure pins to use GPIO peripheral module */
	PORTB->PCR[RED_SHIFT] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_SHIFT] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_SHIFT] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_SHIFT] |= PORT_PCR_MUX(1);
	PORTB->PCR[GREEN_SHIFT] |= PORT_PCR_MUX(1);
	PORTD->PCR[BLUE_SHIFT] |= PORT_PCR_MUX(1);
	
	/* Set LED pins to be outputs */
#ifdef FAST_ACCESS
	FPTB->PDDR |= MASK(RED_SHIFT) | MASK(GREEN_SHIFT);
	FPTD->PDDR |= MASK(BLUE_SHIFT);
#else
	PTB->PDDR |= MASK(RED_SHIFT) | MASK(GREEN_SHIFT);
	PTD->PDDR |= MASK(BLUE_SHIFT);
#endif

	if (display) {
		_red_on();
		_green_off();
		_blue_off();
		delay(DELAY_500_MS);
		
		_red_off();
		_green_on();
		delay(DELAY_500_MS);
		
		_green_off();
		_blue_on();
		delay(DELAY_500_MS);
		
		_blue_off();
	}
}

int rgb_led_on(rgb_color color) {
	switch (color) {
		case RED:
			_red_on();
			break;
		case GREEN:
			_green_on();
			break;
		case BLUE:
			_blue_on();
			break;
	}
	
	return 0;
}

int rgb_led_off(rgb_color color) {
	switch (color) {
		case RED:
			_red_off();
			break;
		case GREEN:
			_green_off();
			break;
		case BLUE:
			_blue_off();
			break;
	}
	
	return 0;
}

int rgb_led_toggle(rgb_color color) {
	switch (color) {
		case RED:
			_red_toggle();
			break;
		case GREEN:
			_green_toggle();
			break;
		case BLUE:
			_blue_toggle();
			break;
	}
	
	return 0;
}

void rgb_white(void) {
	_red_on();
	_green_on();
	_blue_on();
}

void rgb_black(void) {
	_red_off();
	_green_off();
	_blue_off();
}
