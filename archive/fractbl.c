
	.asm
	.linklist
	.symbols
	.endasm

#ifdef INTERNAL
#define __fraction_table __internal_fraction_table
#endif

const double __fraction_table [] =
{
1.0e-1, 1.0e-2, 1.0e-4, 1.0e-8, 1.0e-16, 1.0e-32, 1.0e-64, 1.0e-128, 1.0e-256
};

