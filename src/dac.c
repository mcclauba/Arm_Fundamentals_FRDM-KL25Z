#include <MKL25Z4.h>
#include "../inc/dac.h"
#include "../inc/std_funcs.h"

void dac_init(void)
{
	/* Enable Clock to DAC and PORTE, DAC0 uses PTE30 as output */
	SIM->SCGC6 |= SIM_SCGC6_DAC0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	/* Select analog for pin @ port E */
	PORTE->PCR[DAC_PORT_OUT_POS] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[DAC_PORT_OUT_POS] |= PORT_PCR_MUX(0);
	
	/* Disable buffer mode */
	DAC0->C1 = 0;
	DAC0->C2 = 0;
	
	/* Enable DAC0, select VDDA as reference voltage (what is this value? 3v3?) */
	DAC0->C0 = DAC_C0_DACEN_MASK | DAC_C0_DACRFS_MASK;
}

void dac_generate_triangle(void)
{
	int i = 0, change = 1;
	
	while (1) {
		DAC0->DAT[0].DATL = DAC_DATL_DATA0(i);
		DAC0->DAT[0].DATH = DAC_DATH_DATA1(i >> 8);
		
		i += change;
		if (i == 0) {
			change = 1;
		} else if (i == DAC_RESOLUTION-1) {
			change = -1;
		}
		
		delay(DELAY_1_MS);
	}
}
