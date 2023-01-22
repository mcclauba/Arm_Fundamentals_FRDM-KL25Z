#include <MKL25Z4.h>
#include <stdbool.h>

#include "../inc/rgb.h"
#include "../inc/adc_dac.h"
#include "../inc/cmp.h"
#include "../inc/switch.h"
#include "../inc/timers.h"

int main(void) {
	SystemCoreClockUpdate();

	rgb_init(true); /* Show lights on start-up */
	// cmp_init(true); /* Enable IRQ */
	dac_init();
	systick_init();

	while(1);
}
