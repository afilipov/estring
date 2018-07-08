
#ifdef INTERNAL
#define __printf_char __iprintf_char
#define __cond_pad __internal_cond_pad
#define __output_str __internal_output_str
#define __scanf_char __iscanf_char
#define __unget_scanf_char __iunget_scanf_char
#define __get_printf_ptr_arg __iget_printf_ptr_arg
#define __get_printf_long_arg __iget_printf_long_arg
#define __get_printf_double_arg __iget_printf_double_arg
#define __get_scanf_ptr_arg __iget_scanf_ptr_arg
#define __round __internal_round
#define __decimal_exponent __internal_decimal_exponent
#endif

#include "printf.h"

/******************************************************************************/
/* cond_pad                                                                   */
/******************************************************************************/

	.asm
	.linklist
	.symbols
	.endasm

#ifdef INTERNAL
void __internal_cond_pad (cnt, adj, precision_value, pad_flag, left_justify, min_field_ptr, result_ptr)
#else
void __cond_pad (cnt, adj, precision_value, pad_flag, left_justify, min_field_ptr, result_ptr)
#endif

char cnt;
int  adj;
int  precision_value;
char pad_flag;
char left_justify;
int  *min_field_ptr;
int  *result_ptr;
{
  if (cnt < precision_value)
  {
  cnt = precision_value;			/* adjust for pad */
  }
cnt += adj;					/* add in prefix size */
  if (left_justify == 0)
  {
    while (*min_field_ptr > cnt)
    {
      if (pad_flag)
      {
      __printf_char ('0');			/* zero pad */
      }
      else
      {
      __printf_char (' ');			/* pad with a space */
      }
    ++(*result_ptr);
    --(*min_field_ptr);
    }
  }
*min_field_ptr -= adj;				/* adjust width for prefix */
return;
}

