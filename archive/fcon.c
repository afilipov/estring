
#ifdef INTERNAL
#define __f_convert __internal_f_convert
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
#define __convert_number __internal_convert_number
#define __round __internal_round
#define __decimal_exponent __internal_decimal_exponent
#define strlen istrlen
#endif

#include "printf.h"

/******************************************************************************/
/* f_convert                                                                  */
/******************************************************************************/

	.asm
	.linklist
	.symbols
	.endasm

__f_convert (number, precision_value, dec_point_ptr, negative_ptr, result_ptr, convert, min_field_ptr, pad_flag, sign_char, prefix_flag, left_justify)
double number;
int  precision_value;
int  *dec_point_ptr;
char *negative_ptr;
int  *result_ptr;
char *convert;
int  *min_field_ptr;
char pad_flag;
char sign_char;
char prefix_flag;
char left_justify;
{
int index = 0;
int length;

*negative_ptr = 0;
  if (number < 0.0)
  {
  *negative_ptr = 1;
  number = -number;
  }
number = __round (number, precision_value);
number = __decimal_exponent (number, dec_point_ptr);
  if (*dec_point_ptr > 16)
  {
    for (index = 0; index != 16; ++index)
    {
    __printf_char ('?');
    ++(*result_ptr);
    }
  }
  else
  {
  __convert_number (number, precision_value + *dec_point_ptr, dec_point_ptr, convert);
  length = strlen (convert);			/* get length of string */
    if (*negative_ptr || sign_char != '\0')
    {
    ++length;					/* account for prefix */
    }
    if (precision_value != 0 || prefix_flag)
    {
    ++length;					/* account for decimal pt */
    }
    if (*dec_point_ptr <= 0)
    {
    ++length;					/* account for lead zero */
      if (*dec_point_ptr < 0)
      {
      length += -(*dec_point_ptr);		/* account for extra zeros */
      }
    }
    if (length > *min_field_ptr)
    {
    *min_field_ptr = length;			/* longer than field */
    }
    if (left_justify == 0)
    {
      while (*min_field_ptr > length)
      {
	if (pad_flag)
	{
	__printf_char ('0');
	}
	else
	{
        __printf_char (' ');
	}
      ++(*result_ptr);
      --(*min_field_ptr);			/* decrement field size */
      }
    }
    if (*negative_ptr != 0)
    {
    __printf_char ('-');
    ++(*result_ptr);
    --(*min_field_ptr);				/* decrement field size */
    }
    else
    {
      if (sign_char != '\0')
      {
      __printf_char (sign_char);
      ++(*result_ptr);
      --(*min_field_ptr);
      }
    }
    if (*dec_point_ptr <= 0)
    {
    __printf_char ('0');
    ++(*result_ptr);
    --(*min_field_ptr);
      if (precision_value != 0)
      {
      __printf_char ('.');
      ++(*result_ptr);
      --(*min_field_ptr);
      }
      while (*dec_point_ptr != 0)
      {
      __printf_char ('0');
      ++(*result_ptr);
      --(*min_field_ptr);
      ++(*dec_point_ptr);
      }
    }
    while (*(convert + index) != '\0')		/* output number */
    {
    __printf_char (*(convert + index));
    ++(*result_ptr);
    --(*dec_point_ptr);				/* decrement decimal pos */
    --(*min_field_ptr);				/* decrement field count */
    ++index;					/* point to next character */
      if (*dec_point_ptr == 0)
      {
        if (prefix_flag || precision_value > 0)	/* output decimal point */
        {
	__printf_char ('.');
	++(*result_ptr);
        --(*min_field_ptr);
        }
      (*dec_point_ptr)--;
      }
    }
    while (*min_field_ptr > 0)
    {
    __printf_char (' ');
    ++(*result_ptr);
    --(*min_field_ptr);
    }
  }
}

