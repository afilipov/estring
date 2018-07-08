#include "math.h"
#include "error.h"

	.asm
	.linklist
	.symbols
	.endasm

/*
#define DEBUG_MESSAGES  1
*/

/*****************************************************************************
*        U S E S    F L O A T S    I N S T E A D    O F   D O U B L E S      *
*****************************************************************************/

f_i_floor (x)
float x;
{
int i;

#ifdef DEBUG_MESSAGES
float *f_ptr;
char  *conv_ptr;

printf ("The argument passed to i_floor is %f\n", (double) x);
  f_ptr = &x;
  conv_ptr = (char *) f_ptr;
    for (i = 3; i != -1; i--)
    printf ("conv_ptr -> %x\n", (*(conv_ptr + i) & 0x00ff));
#endif

i = ((int)x);
if ((x < 0.0) && ((x - i) != 0.0))
return (i - 1);
else
return (i);
}

