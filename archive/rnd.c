
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
#endif

#include "printf.h"

/******************************************************************************/
/* round                                                                      */
/******************************************************************************/

	.asm
	.linklist
	.symbols
	.endasm

double __round (number, digits)
double number;
int digits;
{
#ifdef INTERNAL
const double *tmp_dblp;
#else
double *tmp_dblp;
#endif
double tmp_dbl;
int cnt;

  if (digits <= 16 && number != 0.0)
  {
  cnt = 16;				/* assume 16 digits */
  tmp_dbl = 0.5;			/* init to 1/2 */
  tmp_dblp = __fraction_table + 4;	/* init to 1.0e-16 */
    while (tmp_dblp >= __fraction_table)
    {
      if (digits >= cnt)
      {
      tmp_dbl *= *tmp_dblp;		/* multiply by power two */
      digits -= cnt;			/* adjust precision */
      }
    cnt >>= 1;				/* next power of two */
    --tmp_dblp;
    }
  number += tmp_dbl;
  }
return (number);
}

