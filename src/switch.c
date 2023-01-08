#include <MKL25Z4.h>
#include "../inc/switch.h"
#include "../inc/std_funcs.h"

#define IRQ_SW_EITHER_EDGE 11
#define SW_PRIORITY	2

void switch_init(void) {
	/* Enable clock on PORTD */
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	
	/* GPIO module */
	PORTD->PCR[SW1_SHIFT] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[SW1_SHIFT] |= PORT_PCR_MUX(1);
	PORTD->PCR[SW2_SHIFT] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[SW2_SHIFT] |= PORT_PCR_MUX(1);
	
	/* Inputs */
	PTD->PDDR &= ~MASK(SW1_SHIFT);
	PTD->PDDR &= ~MASK(SW2_SHIFT);
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

void switch_irq_init(void) {
	PORTD->PCR[SW1_SHIFT] = 
		PORT_PCR_MUX(1) | /* GPIO */
		PORT_PCR_PS_MASK | /* Pull enable */
		PORT_PCR_PE_MASK | /* Pull-up enable */
		PORT_PCR_IRQC(IRQ_SW_EITHER_EDGE);
	
	PORTD->PCR[SW2_SHIFT] = 
		PORT_PCR_MUX(1) | /* GPIO */
		PORT_PCR_PS_MASK | /* Pull enable */
		PORT_PCR_PE_MASK | /* Pull-up enable */
		PORT_PCR_IRQC(IRQ_SW_EITHER_EDGE);
	
	/* Config NVIC */
	NVIC_SetPriority(PORTD_IRQn, SW_PRIORITY);
	NVIC_ClearPendingIRQ(PORTD_IRQn);
	NVIC_EnableIRQ(PORTD_IRQn);
}
