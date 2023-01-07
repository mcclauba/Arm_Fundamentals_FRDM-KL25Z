#include <MKL25Z4.h>
#include "dac.h"
#include "std_funcs.h"

#define ANALOG_INPUT_CHANNEL 5

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

static void init_positive_input_pin(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	/* Set pin PE29 to use the specified analog input channel */
	PORTE->PCR[CMP_PORT_IN_POS] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[CMP_PORT_IN_POS] = PORT_PCR_MUX(ANALOG_INPUT_CHANNEL) | PORT_PCR_PE_MASK;
}

void comparator_init(void)
{
	init_positive_input_pin();
	
	/* Enable clock to comparator, enable */
	SIM->SCGC4 |= SIM_SCGC4_CMP_MASK;
	CMP0->CR1 = CMP_CR1_EN_MASK;

	/* Select input channels,
	 * Plus: channel 5 on Port E bit 29
	 * Minus: channel 7 is CMP DAC
	 */
	CMP0->MUXCR = CMP_MUXCR_PSEL(5) | CMP_MUXCR_MSEL(7);
	
	/* Enable CMP's DAC, set reference voltage to 1.85V
	 * CMP's internal DAC has a 6-bit resolution (64)
	 * 64 * 1.85/3.3V ~= 36
	 */
	CMP0->DACCR = CMP_DACCR_DACEN_MASK | CMP_DACCR_VOSEL(36);
	
	/* Enable interrupt on both rising and falling edges */
	CMP0->SCR = CMP_SCR_IEF_MASK | CMP_SCR_IER_MASK;

	NVIC_SetPriority(CMP0_IRQn, 128);
	NVIC_ClearPendingIRQ(CMP0_IRQn);
	NVIC_EnableIRQ(CMP0_IRQn);
}

void generate_triangle(void)
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
