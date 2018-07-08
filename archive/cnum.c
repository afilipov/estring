
#ifdef INTERNAL
#define __convert_number __internal_convert_number
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
#endif

#include "printf.h"

/******************************************************************************/
/* convert_number                                                             */
/******************************************************************************/

	.asm
	.linklist
	.symbols
	.endasm

__convert_number (number, digits, dec_pt, convert)
double number;
int  digits;
int  *dec_pt;
char *convert;
{
int tmp_val;
int tmp_digits;
char *buf_ptr;

  if (number == 0.0)			/* check for 0 */
  {
  *dec_pt = 0;				/* no fraction */
  *convert = '0';			/* store leading 0 */
  *(convert + 1) = '\0';
  }
  if (digits > CONVERT_SIZE)
  {
  digits = CONVERT_SIZE;		/* no buffer overflow */
  }
buf_ptr = convert;			/* point to buffer */
tmp_digits = 16;
  while (tmp_digits > 0 && digits > 0)
  {
  tmp_val = number;			/* get whole number part */
    if (tmp_val > number)
    {
    tmp_val--;
    }
  *buf_ptr++ = tmp_val + '0';		/* convert to ascii */
  number -= tmp_val;
  number *= 10.0;			/* get new number */
  --tmp_digits;
  --digits;				/* decrement digit counts */
  }
  while (digits > 0)
  {
  *buf_ptr++ = '0';			/* store trailing zeros */
  --digits;				/* decrement digit count */
  }
*buf_ptr = '\0';
}

