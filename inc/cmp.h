#define ANALOG_INPUT_CHANNEL 0
#define CMP_PORT_IN_POS (29) /* Port E */
#define CMP_COUT (CMP0->SCR & CMP_SCR_COUT_MASK)

void cmp_init(void);
