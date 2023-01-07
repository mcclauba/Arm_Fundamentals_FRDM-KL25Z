#include <stdint.h>
#include <stdbool.h>
#include "std_funcs.h"

#define RED_SHIFT (18) /* PORTB */
#define GREEN_SHIFT (19) /* PORTB */
#define BLUE_SHIFT (1) /* PORTD */

#define FLASH_W_ON	(uint8_t)1
#define FLASH_W_OFF	(uint8_t)0

typedef enum { 
	RED = 0, 
	GREEN, 
	BLUE
} rgb_color;

/**
 * @brief Initialize RGB LEDs on Freedom board
 */
void rgb_init(bool display);

/**
 * @brief Turn on desired LED as determined by rgb_led
 * @params[in] rgb_led LED color to turn on 
 */
int rgb_led_on(rgb_color color);

/**
 * @brief Turn off desired LED as determined by rgb_led
 * @params[in] rgb_led LED color to turn off 
 */
int rgb_led_off(rgb_color color);

/**
 * @brief Toggle desired LED as determined by rgb_led
 * @params[in] rgb_led LED color to toggle 
 */
int rgb_led_toggle(rgb_color color);

void rgb_white(void);
void rgb_black(void);

/**
 * @brief Flash RGB according to values of global rgb_* variables
 */
void TaskRGB(void);

/**
 * @brief Flash white/black according to values of global rgb_* variables
 */
void TaskWhite(void);
