
#include "math.h"
#include "error.h"

	.asm
	.symbols
	.linklist
	.endasm

double fabs (x)
double x;
{
if (x < 0.0)
return (-x);
else
return (x);
}


