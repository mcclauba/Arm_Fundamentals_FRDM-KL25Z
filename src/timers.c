#include <MKL25Z4.h>
#include "../inc/timers.h"
#include "../inc/adc_dac.h"

#define SYSTICK_USE_PROCESSOR_CLK 1

#ifdef SYSTICK_USE_PROCESSOR_CLK
#define CLK_SPEED 48 * 1000UL * 1000UL
#else
#define CLK_SPEED 3 * 1000UL * 1000UL
#endif

// #define SYSTICK_IRQ_INTERVAL_NS(x/CLK_SPEED)

void SysTick_Handler(void);

/**
 *  SysTick 
 */
void systick_init(void)
{
    SysTick->LOAD = (999UL); /* 1ms */

    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_TICKINT_Msk /* Enable interrupt when counter reaches 0 */
                  | SysTick_CTRL_ENABLE_Msk /* Enable SysTick Timer */
                  | SysTick_CTRL_CLKSOURCE_Msk; /* Use processor clock */

    /* NVIC */
    NVIC_SetPriority(SysTick_IRQn, 3);
}

void SysTick_Handler(void)
{
    dac_generate_triangle();
}

/**
 * Watchdog
 */

/**
 * @brief Intialize watchdog timer
 * Use 1 kHz clock with timeout after 1024 cycles = 1.024 seconds
*/
void COP_WDT_init(void)
{
    SIM_COPC = 0xC;

    // SIM->COPC = SIM_COPC_COPT(3) /* COP timeout after 2^10 LPO cycles or 2^18 bus clock cycles */
    //           & ~SIM_COPC_COPCLKS_MASK; /* Internal 1 kHz clock is source to COP, alternatively can use 24 MHz bus clock */
}

void COP_WDT_service(void)
{
    SIM->SRVCOP = 0x55;
    SIM->SRVCOP = 0xaa;
}

void COP_WDT_service_fail(void)
{
    SIM->SRVCOP = 0xff;
}
