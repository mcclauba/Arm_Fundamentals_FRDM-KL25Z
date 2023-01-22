#include <MKL25Z4.h>
#include "../inc/timers.h"
#include "../inc/rgb.h"
#include "../inc/adc_dac.h"

#define SYSTICK_USE_PROCESSOR_CLK 1

#ifdef SYSTICK_USE_PROCESSOR_CLK
#define CLK_SPEED 48 * 1000UL * 1000UL
#else
#define CLK_SPEED 3 * 1000UL * 1000UL
#endif

// #define SYSTICK_IRQ_INTERVAL_NS(x/CLK_SPEED)

void SysTick_Handler(void);

/* SysTick */
void systick_init(void)
{
    SysTick->LOAD = (999UL); /* Number of clock pulses til interrupt triggers */

    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_TICKINT_Msk /* Enable interrupt when counter reaches 0 */
                  | SysTick_CTRL_ENABLE_Msk; /* Enabel SysTick Timer */

    /* NVIC */
    NVIC_SetPriority(SysTick_IRQn, 3);
}

void SysTick_Handler(void)
{
    dac_generate_triangle();
    
    // static int n=0;

    // if (n&1) {
    //     rgb_led_on(GREEN);
    //     rgb_led_off(BLUE);
    // } else {
    //     rgb_led_off(GREEN);
    //     rgb_led_on(BLUE);
    // }

    // n++;
}
