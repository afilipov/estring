
#include "math.h"
#include "error.h"

#ifdef INTERNAL
#define printf internal_nf_printf
#endif

	.asm
	.linklist
	.symbols
	.endasm

/*
#define DEBUG_MESSAGES  1
*/

i_floor (x)
double x;
{
int i;
#ifdef DEBUG_MESSAGES
double *f_ptr;
char   *conv_ptr;
#endif

#ifdef DEBUG_MESSAGES
printf ("The argument passed to i_floor is %f\n", x);
  f_ptr = &x;
  conv_ptr = (char *) f_ptr;
    for (i = 7; i != -1; i--)
    printf ("conv_ptr -> %x\n", (*(conv_ptr + i) & 0x00ff));
#endif

i = ((int)x);
if ((x < 0.0) && ((x - i) != 0.0))
return (i - 1);
else
return (i);
}

