#define SW1_SHIFT 2 /* PORTD */
#define SW2_SHIFT 3 /* PORTD */
#define IRQ_SW_EITHER_EDGE 11
#define SW_PRIORITY					2

#define SWITCH_PRESSED(x) (!(PTD->PDIR & MASK(x))) /* Logical 0 if swtich pressed */
#define SW_IRQ(x)	(PORTD->ISFR & MASK(x))
#define CLEAR_SW_IRQ(x)	(PORTD->ISFR &= ~(1UL << x))

void switch_init(void);

void switch_irq_init(void);
