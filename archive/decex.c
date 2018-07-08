
#ifdef INTERNAL
#define __cprintf __internal_cprintf
#define __printf_char __iprintf_char
#define __cond_pad __internal_cond_pad
#define __output_str __internal_output_str
#define __scanf_char __iscanf_char
#define __unget_scanf_char __iunget_scanf_char
#define __get_printf_int_arg __iget_printf_int_arg
#define __get_printf_ptr_arg __iget_printf_ptr_arg
#define __get_printf_long_arg __iget_printf_long_arg
#define __get_printf_double_arg __iget_printf_double_arg
#define __get_scanf_ptr_arg __iget_scanf_ptr_arg
#define __round __internal_round
#define __decimal_exponent __internal_decimal_exponent
#define __fraction_table __internal_fraction_table
#define __power_table __internal_power_table
#endif

#include "printf.h"

/******************************************************************************/
/* decimal_exponent                                                           */
/******************************************************************************/

	.asm
	.linklist
	.symbols
	.endasm

double __decimal_exponent (number, exp_ptr)
double number;
int *exp_ptr;
{
int index;

  if (number == 0.0)
  {
  *exp_ptr = 0;				/* no exponent */
  }
  else
  {
  *exp_ptr = 1;				/* init exponent */
    if (number >= 1.0)			/* get decimal exponent */
    {
      for (index = 8; index >= 0; index--)
      {
        if (number >= __power_table[index])
	{
	number *= __fraction_table[index];
	*exp_ptr += 1 << index;
	}
      }
    }
    else
    {
      for (index = 8; index >= 0; index--)
      {
        if (number <= __fraction_table[index])
	{
	number *= __power_table[index];
	*exp_ptr -= 1 << index;
	}
	if(number < 1.0)
	{
	number *= 10.0;
	--(*exp_ptr);
	}
      }
    }
  }
return (number);
}

