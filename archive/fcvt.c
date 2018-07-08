
	.asm
	.linklist
	.symbols
	.endasm

#ifdef INTERNAL
#define fcvt ifcvt
#define __round __internal_round
#define __decimal_exponent __internal_decimal_exponent
#define __fraction_table __internal_fraction_table
#define __power_table __internal_power_table
#endif

#include "printf.h"

char *fcvt (number, digits, decimal_point, sign, buffer)
double number;
int digits;
int *decimal_point;
int *sign;
char *buffer;
{
char  digit;
char *temp_ptr;

temp_ptr = buffer;			/* save destination pointer */
  if (number < 0.0)
  {
  *sign = 1;
  -number;				/* must be positive */
  }
  else
  {
  *sign = 0;
  }
number = __round (number, digits + 1);
number = __decimal_exponent (number, decimal_point);
digits += *decimal_point;
  while (digits > 0)
  {
  digit = number;			/* get whole number part */
    if (digit > number)
    {
    digit--;
    }
  *temp_ptr++ = digit + '0';		/* store digit */
  number -= digit;
  number *= 10.0;			/* get new number */
  digits--;				/* decrement digit count */
  }
*temp_ptr = '\0';			/* terminate */
return (buffer);
}

