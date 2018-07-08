
	.asm
	.linklist
	.symbols
	.endasm

#ifdef INTERNAL
#define __power_table __internal_power_table
#endif

const double __power_table [] =
{
1.0e1, 1.0e2, 1.0e4, 1.0e8, 1.0e16, 1.0e32, 1.0e64, 1.0e128, 1.0e256
};

