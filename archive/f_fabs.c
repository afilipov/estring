
#include "math.h"
#include "error.h"

	.asm
	.linklist
	.symbols
	.endasm


/*****************************************************************************
*        U S E S    F L O A T S    I N S T E A D    O F   D O U B L E S      *
*****************************************************************************/

float f_fabs (x)
float x;
{
if (x < 0.0)
return (-x);
else
return (x);
}


