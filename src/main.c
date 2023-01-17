#include <MKL25Z4.h>
#include <stdbool.h>

#include "../inc/std_funcs.h"
#include "../inc/rgb.h"
#include "../inc/adc_dac.h"
#include "../inc/cmp.h"
#include "../inc/switch.h"

int main(void) {
	SystemCoreClockUpdate();

	rgb_init(true);
	porte29_analog_in();
	cmp_init(true);
	dac_init();

	dac_generate_triangle();
}
