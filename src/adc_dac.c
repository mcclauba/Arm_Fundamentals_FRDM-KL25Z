#include <MKL25Z4.h>

#include "../inc/adc_dac.h"
#include "../inc/std_funcs.h"
#include "../inc/rgb.h"

#define DAC_PORT_OUT_POS (30)	/* Port E */
#define DAC_RESOLUTION 4096

#define ADC_IN (20) /* PORT E */

void dac_init(void)
{
	/* Enable Clock to DAC and PORTE, DAC0 uses PTE30 as output */
	SIM->SCGC6 |= SIM_SCGC6_DAC0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	/* Select analog out for pin @ port E */
	PORTE->PCR[DAC_PORT_OUT_POS] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[DAC_PORT_OUT_POS] |= PORT_PCR_MUX(0);
	
	/* Disable buffer mode */
	DAC0->C1 = 0;
	DAC0->C2 = 0;
	
	/* Enable DAC0, select VDDA as reference voltage */
	DAC0->C0 = DAC_C0_DACEN_MASK | DAC_C0_DACRFS_MASK;
}

void dac_generate_triangle(void)
{
	static int i = 0;
	static int change = 1;
	
	DAC0->DAT[0].DATL = DAC_DATL_DATA0(i);
	DAC0->DAT[0].DATH = DAC_DATH_DATA1(i >> 8);
	
	i += change;
	if (i == 0) {
		change = 1;
	} else if (i == DAC_RESOLUTION-1) {
		change = -1;
	}
}

void adc_init(void)
{
	/* Enable clock to PORTE and ADC */
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

	/* Select analog for pin 20 on Port E */
	PORTE->PCR[ADC_IN] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[ADC_IN] |= PORT_PCR_MUX(0);

	/* ADC configurations */
	ADC0->CFG1 = 
		ADC_CFG1_ADLPC_MASK | 	/* low power */
		ADC_CFG1_ADLSMP_MASK | 	/* long sample time */
		ADC_CFG1_MODE(3) | 		/* 16 bit single-ended conversion */
		ADC_CFG1_ADICLK(0); 	/* bus clock input */
	
	/* Software trigger, compare function disabled, DMA disabled, 
	   voltage references VREFH and VREGL */
	ADC0->SC2 = ADC_SC2_REFSEL(0);
}

float adc_read(void)
{
	float value = 0;

	/* Start conversion on channel 0 */
	ADC0->SC1[0] = 0x00;

	/* Wait for conversion to finish */
	while (!(ADC0->SC1[0] & ADC_SC1_COCO_MASK))

	/* Read analog value */
	value = (float) ADC0->R[0];

	return value;
}

void adc_task(void)
{
	float adc_value = 0;
	float threshold = (float)1.85;
	
	while (1) {
		adc_value = adc_read();
		if (adc_value < threshold) { 
			rgb_led_off(RED);
			rgb_led_on(GREEN);
		} else {
			rgb_led_on(RED);
			rgb_led_off(GREEN);
		}
	}
}
