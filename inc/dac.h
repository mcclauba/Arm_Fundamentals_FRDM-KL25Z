
#define DAC_PORT_OUT_POS (30)	/* Port E */
#define CMP_PORT_IN_POS (29) /* Port E */
#define DAC_RESOLUTION 4096

void dac_init(void);

void comparator_init(void);

void generate_triangle(void);
