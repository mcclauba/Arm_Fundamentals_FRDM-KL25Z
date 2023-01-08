#include <MKL25Z4.h>
#include <stdbool.h>

#include "../inc/std_funcs.h"
#include "../inc/rgb.h"
#include "../inc/dac.h"
#include "../inc/cmp.h"
#include "../inc/switch.h"

void CMP0_IRQHandler(void)
{
	/* *** Consider setting break point here */
	if (CMP0->SCR & CMP_SCR_CFR_MASK) { 
		/* Rising edge, green light */
		rgb_led_off(RED);
		rgb_led_on(GREEN);
		rgb_led_off(BLUE);
	} else if (CMP0->SCR & CMP_SCR_CFF_MASK) {
		/* Falling edge, red light */
		rgb_led_on(RED);
		rgb_led_off(GREEN);
		rgb_led_off(BLUE);
	} else {
		rgb_led_off(RED);
		rgb_led_off(GREEN);
		rgb_led_on(BLUE);
	}
	
	/* Clear flags, keep both rising and falling edges enabled */
	CMP0->SCR = CMP_SCR_IEF_MASK | CMP_SCR_IER_MASK | CMP_SCR_CFR_MASK | CMP_SCR_CFF_MASK;
}

int main(void) {
	SystemCoreClockUpdate();

	rgb_init(true);
	porte29_digital_in();
	cmp_init();
	//dac_init();
	//dac_generate_triangle();

	// while (1) {
	// 	if (CMP_COUT) {
	// 		rgb_led_on(GREEN);
	// 		rgb_led_off(RED);
	// 	} else {
	// 		rgb_led_on(RED);
	// 		rgb_led_off(GREEN);
	// 	}
	// }

	while (1);
	
	return 0;
}
