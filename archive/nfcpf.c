
#ifdef INTERNAL
#define __nf_cprintf __internal_nf_cprintf
#define __printf_char __iprintf_char
#define __cond_pad __internal_cond_pad
#define __output_str __internal_output_str
#define __scanf_char __iscanf_char
#define __unget_scanf_char __iunget_scanf_char
#define __get_printf_char_arg __iget_printf_char_arg
#define __get_printf_int_arg __iget_printf_int_arg
#define __get_printf_ptr_arg __iget_printf_ptr_arg
#define __get_printf_long_arg __iget_printf_long_arg
#define __get_printf_double_arg __iget_printf_double_arg
#define __get_scanf_ptr_arg __iget_scanf_ptr_arg
#define __round __internal_round
#define __decimal_exponent __internal_decimal_exponent
#define __convert_number __internal_convert_number
#define __f_convert __internal_f_convert
#define strlen istrlen
#endif

#include "printf.h"

/******************************************************************************/
/* NON-FORMATTING CHAR, INT, LONG, FLOAT & DOUBLE PRINTF                      */
/******************************************************************************/

	.asm
	.linklist
	.symbols
	.endasm

__nf_cprintf (printf_ptr)

#ifdef INTERNAL
const char *printf_ptr;
#else
char *printf_ptr;
#endif

{
char digit;
char sign_char;
char prefix_flag;
char long_flag;
char lower_flag;
char pad_flag;

int result = 0;
int precision;
int decimal_point;
int exponent;

char *string;

unsigned long ulong;
unsigned long ulong1;

double dbl1;

  while (*printf_ptr != '\0')
  {
    if (*printf_ptr != '%')
    {
    __printf_char (*printf_ptr);		/* output character */
    ++result;
    ++printf_ptr;
    }
    else
    {
    ++printf_ptr;				/* point past % */
    sign_char = '\0';				/* init flags */
    prefix_flag = 0;
    long_flag = 0;
    lower_flag = 0;
    pad_flag = 0;
    precision = 0;
    decimal_point = 0;
      while (1)					/* check flags */
      {
	if (*printf_ptr == '0')			/* check pad flag */
	{
	pad_flag = 1;
	}
        else if (*printf_ptr == ' ')		/* check space flag */
        {
        sign_char = ' ';
	}
	else if (*printf_ptr == '+')		/* check sign flag */
	{
        sign_char = '+';
	}
	else if (*printf_ptr == '#')		/* check prefix flag */
	{
        prefix_flag = 1;
        }
	else
	{
	break;					/* not a flag get out */
	}
      ++printf_ptr;				/* point to next character */
      }

      while (*printf_ptr >= '0' && *printf_ptr <= '9')
      {
      precision = (precision * 10) + (*printf_ptr - '0');
      ++printf_ptr;
      }

      if (*printf_ptr == 'l')			/* check long flag */
      {
      long_flag = 1;
      ++printf_ptr;
      }

      switch (*printf_ptr)			/* check for a conversion */
      {
      case 'x':
        lower_flag = 1;
      case 'X':
        ++printf_ptr;
          if (long_flag)
          {
          ulong = __get_printf_long_arg ();
	  ulong1 = LONG_MAX_POWER_OF_SIXTEEN;
          }
          else
          {
          ulong = __get_printf_int_arg ();
	  ulong1 = INT_MAX_POWER_OF_SIXTEEN;
          }
	  if (prefix_flag)
	  {
	  __printf_char ('0');			/* output hex prefix */
	    if (lower_flag)
	    {
	    __printf_char ('x');
	    }
	    else
	    {
	    __printf_char ('X');
	    }
	  result += 2;
	  }
	  if (pad_flag == 0 && ulong == 0l)
	  {
	  __printf_char ('0');			/* zero is a special case */
	  ++result;
	  }
	  else
	  {
            do					/* make at least one pass */
            {
	    digit = ulong / ulong1;		/* convert digit */
	    ulong %= ulong1;			/* save remainder */
              if (digit > 9)
              {
 	        if (lower_flag)			/* convert to a - f or A - F */
	        {
	        digit += 0x27;
	        }
 	        else
	        {
	        digit += 7;
	        }
              }
	    digit += '0';
	      if (pad_flag || digit != '0')
	      {
	      pad_flag = 1;			/* keep trailing zeros */
	      __printf_char (digit);		/* output byte */
	      ++result;
	      }
	    ulong1 /= 16;			/* decrease divisor */
            }
            while (ulong1 != 0);
	  }
      break;

      case 'd':
        ++printf_ptr;
          if (long_flag)
          {
          ulong = __get_printf_long_arg ();
	  ulong1 = LONG_MAX_POWER_OF_TEN;
          }
          else
          {
          ulong = __get_printf_int_arg ();
	    if (ulong & 0x8000l)
	    {
	    ulong |= 0xffff0000l;		/* sign extend */
	    }
	  ulong1 = INT_MAX_POWER_OF_TEN;
          }
          if (ulong & 0x80000000l)
          {
	  ulong = ~ulong + 1;			/* complement */
	  __printf_char ('-');			/* output sign */
	  ++result;
          }
	  else
	  {
	    if (sign_char != '\0')		/* output + */
	    {
	    __printf_char (sign_char);
	    ++result;
	    }
	  }
	  if (pad_flag == 0 && ulong == 0l)
	  {
	  __printf_char ('0');			/* zero is a special case */
	  ++result;
	  }
	  else
	  {
            do
            {
	    digit = ulong / ulong1;		/* convert digit */
	    digit += '0';
	    ulong %= ulong1;			/* save remainder */
	      if (pad_flag || digit != '0')
	      {
	      pad_flag = 1;			/* keep trailing zeros */
	      __printf_char (digit);		/* output digit */
	      ++result;
	      }
	    ulong1 /= 10;			/* decrease divisor */
            }
            while (ulong1 != 0);
	  }
      break;

      case 'u':
        ++printf_ptr;
          if (long_flag)
          {
          ulong = __get_printf_long_arg ();
	  ulong1 = LONG_MAX_POWER_OF_TEN;
          }
          else
          {
          ulong = __get_printf_int_arg ();
	  ulong1 = INT_MAX_POWER_OF_TEN;
          }
	  if (pad_flag == 0 && ulong == 0l)
	  {
	  __printf_char ('0');			/* zero is a special case */
	  ++result;
	  }
	  else
	  {
            do
            {
	    digit = ulong / ulong1;		/* convert digit */
	    digit += '0';
	    ulong %= ulong1;			/* save remainder */
	      if (pad_flag || digit != '0')
	      {
	      pad_flag = 1;			/* keep trailing zeros */
	      __printf_char (digit);		/* output digit */
	      ++result;
	      }
	    ulong1 /= 10;			/* decrease divisor */
            }
            while (ulong1 != 0);
	  }
      break;

      case 'o':
        ++printf_ptr;
          if (long_flag)
          {
          ulong = __get_printf_long_arg ();
	  ulong1 = LONG_MAX_POWER_OF_EIGHT;
          }
          else
          {
          ulong = __get_printf_int_arg ();
	  ulong1 = INT_MAX_POWER_OF_EIGHT;
          }
	  if (prefix_flag)
	  {
	  __printf_char ('0');			/* output prefix */
	  ++result;
	  }
	  if (pad_flag == 0 && ulong == 0l)
	  {
	  __printf_char ('0');			/* zero is a special case */
	  ++result;
	  }
	  else
	  {
            do
            {
	    digit = ulong / ulong1;		/* convert digit */
	    digit += '0';
	    ulong %= ulong1;			/* save remainder */
	      if (pad_flag || digit != '0')
	      {
	      pad_flag = 1;			/* keep trailing zeros */
	      __printf_char (digit);		/* output digit */
	      ++result;
	      }
	    ulong1 /= 8;			/* decrease divisor */
            }
            while (ulong1 != 0);
	  }
      break;

      case 'c':
        ++printf_ptr;
        digit = __get_printf_char_arg ();	/* get character */
        __printf_char (digit);			/* output character */
        ++result;
      break;

      case 's':
        ++printf_ptr;
        string = __get_printf_ptr_arg ();	/* get arg pointer */
          while (*string != '\0')
          {
	  __printf_char (*string++);		/* output next character */
	  ++result;
          }
      break;

      case '%':
        ++printf_ptr;
	__printf_char ('%');			/* output percent sign */
	++result;
      break;

      case 'e':
      case 'E':
      case 'f':
      case 'g':
      case 'G':
	dbl1 = __get_printf_double_arg ();
	  if (precision == 0)
	  {
	  precision = 6;			/* default precision */
	  }
	  if (dbl1 < 0)
	  {
	  __printf_char ('-');			/* output sign */
	  ++result;
	  dbl1 = -dbl1;				/* must be positive */
	  }
	  else
	  {
	    if (sign_char != '\0')
	    {
	    __printf_char (sign_char);
	    ++result;
	    }
	  }
	  if (dbl1 == 0.0)			/* check for 0 */
	  {
	  __printf_char ('0');			/* output leading zero */
	  __printf_char ('.');			/* output decimal point */
	  result += 2;
	    while (precision > 0)
	    {
	    __printf_char ('0');		/* output trailing zeros */
	    ++result;
	    --precision;
	    }
	  }
	  else
	  {
	  dbl1 = __decimal_exponent (dbl1, &decimal_point);
	  dbl1 = __round (dbl1, (precision+decimal_point)-1);
	    if (*printf_ptr == 'f')		/* f format ? */
	    {
	      if (decimal_point < -16 || decimal_point > 16)
	      {
	        for (precision = 0; precision != 16; ++precision)
		{
		__printf_char ('?');
		++result;
		}	
	      goto done;
	      }
	    }
	    else if (*printf_ptr == 'g' || *printf_ptr == 'G')
	    {
	      if (decimal_point < -4 || decimal_point > precision)
	      {
	        if (dbl1 > 10.0)
	        {
	        ++decimal_point;
	        dbl1 /= 10.0;
	        }
	      exponent = decimal_point - 1;
	      decimal_point = 1;
	      goto convert_number;
	      }
	    }
	    else
	    {
	      if (dbl1 > 10.0)
	      {
	      ++decimal_point;
	      dbl1 /= 10.0;
	      }
	    exponent = decimal_point - 1;
	    decimal_point = 1;
	    goto convert_number;
	    }
	  exponent = 0;
	  precision = precision + decimal_point;
	    if (decimal_point <= 0)
	    {
	    __printf_char ('0');		/* output leading zero */
	    ++result;
	    __printf_char ('.');		/* output decimal point */
	      while (decimal_point < 0)
	      {
	      __printf_char ('0');
	      ++result;
	      ++decimal_point;
	      }
	    }
convert_number:
	    while (precision > 0)
	    {
	    digit = dbl1;			/* get whole number part */
	      if (digit > dbl1)
	      {
	      digit--;
	      }
	    __printf_char (digit + '0');	/* output digit */
	    ++result;
	    dbl1 -= digit;
	    dbl1 *= 10.0;			/* get new number */
	    --precision;			/* decrement digit counts */
	    --decimal_point;
	      if (decimal_point == 0)
	      {
	      __printf_char ('.');		/* output decimal point */
	      ++result;
	      }
	    }
	    if (exponent != 0)			/* now output exponent */
	    {
	      if (*printf_ptr == 'g')
	      {
	      __printf_char ('e');
	      }
	      else if (*printf_ptr == 'G')
	      {
	      __printf_char ('E');
	      }
	      else
	      {
	      __printf_char (*printf_ptr);
	      }
	      if (exponent < 0)			/* negative exponent ? */
	      {
	      exponent = -exponent;		/* yes, make it positive */
	      __printf_char ('-');
	      }
	      else
	      {
	      __printf_char ('+');		/* no */
	      }
	    __printf_char (exponent / 100 + '0');
	    exponent %= 100;
	    __printf_char (exponent / 10 + '0');
	    __printf_char (exponent % 10 + '0');
	    result += 5;
	    }
	  }
done:
	++printf_ptr;
      break;
      }
    }
  }
return (result);
}

