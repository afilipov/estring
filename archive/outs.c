
#ifdef INTERNAL
#define __printf_char __iprintf_char
#define __output_str __internal_output_str
#define __cond_pad __internal_cond_pad
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
/* output_str                                                                 */
/******************************************************************************/

	.asm
	.linklist
	.symbols
	.endasm

void __output_str (cnt, sptr, precision_value_ptr, pad_flag, min_field_ptr, result_ptr)
char cnt;
char *sptr;
int  *precision_value_ptr;
char pad_flag;
int  *min_field_ptr;
int  *result_ptr;
{
int dcnt;
char ch;

pad_flag = 0;				/* clear padding flag */
dcnt = cnt;
  while (*precision_value_ptr > cnt)	/* zero pad to precision */
  {
  __printf_char ('0');
  ++(*result_ptr);
  --(*precision_value_ptr);
  --(*min_field_ptr);
  }
  while (dcnt != 0)			/* output value */
  {
  ch = *sptr++;
  __printf_char (ch);
  ++(*result_ptr);
  --dcnt;
  (*min_field_ptr)--;
  }
  while (*min_field_ptr > 0)		/* right fill field */
  {
  __printf_char (' ');
  ++(*result_ptr);
  --(*min_field_ptr);
  }
return;
}

