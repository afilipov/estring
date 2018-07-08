
#ifdef INTERNAL
#define __icprintf __internal_icprintf
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
#define strlen istrlen
#endif

#include "printf.h"

/******************************************************************************/
/* CHAR, INT & LONG PRINTF                                                    */
/******************************************************************************/

	.asm
	.linklist
	.symbols
	.endasm

__icprintf (printf_ptr)

#ifdef INTERNAL
const char *printf_ptr;
#else
char *printf_ptr;
#endif

{
char i;
char ch;
char sign_char;
char pad_flag;
char long_flag;
char prefix_flag;
char left_justify;
char precision_flag;
char lower_flag;
char negative;
char convert_buffer[17];
char *conv_ptr;
char *cbuf;

int result = 0;
int min_field;
int precision_value;

unsigned long ulong;

  while (*printf_ptr != '\0')
  {
    if (*printf_ptr != '%')
    {
    __printf_char (*printf_ptr);
    ++printf_ptr;
    ++result;
    }
    else
    {
    ++printf_ptr;				/* point past % */
    sign_char = '\0';				/* init flags */
    pad_flag = 0;
    long_flag = 0;
    negative = 0;
    prefix_flag = 0;
    lower_flag = 0;
    left_justify = 0;
    min_field = 0;
    precision_flag = 0;
    precision_value = 1;
    cbuf = convert_buffer + (sizeof (convert_buffer) - 1);
      while (1)
      {
        if (*printf_ptr == '-')			/* check left justify flag */
        {
        left_justify = 1;
        }
	else if (*printf_ptr == '0')		/* check for zero pad flag */
        {
        pad_flag = 1;
        }
	else if (*printf_ptr == ' ')		/* check for space flag */
        {
        sign_char = ' ';
        }
	else if (*printf_ptr == '+')		/* check for sign flag */
	{
        sign_char = '+';
        }
	else if (*printf_ptr == '#')		/* check prefix flag */
        {
        prefix_flag = 1;
        }
	else
	{
	break;					/* not a flag */
	}
      ++printf_ptr;				/* next character */
      }
      if (*printf_ptr == '*')			/* check for field width */
      {
      min_field = __get_printf_int_arg ();
      ++printf_ptr;
      }
      else
      {
        while (*printf_ptr >= '0' && *printf_ptr <= '9')
        {
        min_field = (min_field * 10) + (*printf_ptr - '0');
        ++printf_ptr;
        } 
      }
      if (*printf_ptr == '.')			/* check for precision */
      {
      ++printf_ptr;
      precision_flag = 1;
      precision_value = 0;
	if (*printf_ptr == '*')
	{
        precision_value = __get_printf_int_arg ();
        ++printf_ptr;
	}
	else
	{
          while (*printf_ptr >= '0' && *printf_ptr <= '9')
          {
          precision_value = (precision_value * 10) + (*printf_ptr - '0');
          ++printf_ptr;
          }
        }
      }
      if (*printf_ptr == 'l')			/* check for long flag */
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
          }
          else
          {
          ulong = __get_printf_int_arg ();
          }
        i = 0;					/* zero digit count */
          do					/* make at least one pass */
          {
	  ch = ulong % 16;			/* convert to ascii */
          ulong /= 16;
            if (ch > 9)
            {
 	      if (lower_flag)
	      {
	      ch += 0x27;
	      }
 	      else
	      {
	      ch += 7;
	      }
            }
          *cbuf-- = ch + '0';			/* store in conversion buffer */
	  ++i;					/* increment digit count */
          }
          while (ulong != 0);
        ++cbuf;					/* back up one */
          if (prefix_flag)
          {
          __cond_pad (i, 2, precision_value, pad_flag,
				left_justify, &min_field, &result);
          __printf_char ('0');
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
          else
          {
          __cond_pad (i, 0, precision_value, pad_flag,
				left_justify, &min_field, &result);
          }
        __output_str (i, cbuf, &precision_value, pad_flag,
				&min_field, &result);
      break;

      case 'd':
	++printf_ptr;
          if (long_flag)
          {
          ulong = __get_printf_long_arg ();
          }
          else
          {
          ulong = __get_printf_int_arg ();
	    if (ulong & 0x8000l)
	    {
	    ulong |= 0xffff0000l;		/* sign extend */
	    }
          }
          if (ulong & 0x80000000l)
          {
          negative = 1;
	  ulong = ~ulong + 1;			/* complement */
          }
        i = 0;					/* zero digit count */
          do
          {
          ch = ulong % 10;			/* get digit and convert */
	  ulong /= 10;
          *cbuf-- = ch + '0';
          ++i;					/* increment digit count */
          }
          while (ulong != 0);
        ++cbuf;					/* back up 1 */
          if (negative)
          {
          __cond_pad (i, 1, precision_value, pad_flag,
				left_justify, &min_field, &result);
	  __printf_char ('-');
	  ++result;
          }
          else
          {
            if (sign_char != '\0')
            {
            __cond_pad (i, 1, precision_value, pad_flag,
				left_justify, &min_field, &result);
	    __printf_char (sign_char);
	    ++result;
            }
            else
            {
            __cond_pad (i, 0, precision_value, pad_flag,
				left_justify, &min_field, &result);
            }
          }
        __output_str (i, cbuf, &precision_value, pad_flag,
				&min_field, &result);
      break;

      case 'u':
	++printf_ptr;
          if (long_flag)
          {
          ulong = __get_printf_long_arg ();
          }
          else
          {
          ulong = __get_printf_int_arg ();
          }
        i = 0;					/* zero digit count */
          do
          {
          ch = ulong % 10;			/* get digit and convert */
	  ulong /= 10;
          *cbuf-- = ch + '0';
          ++i;
          }
          while (ulong != 0);
        ++cbuf;					/* back up 1 */
        __cond_pad (i, 0, precision_value, pad_flag,
				left_justify, &min_field, &result);
        __output_str (i, cbuf, &precision_value, pad_flag,
				&min_field, &result);
      break;

      case 'o':
	++printf_ptr;
          if (long_flag)
          {
          ulong = __get_printf_long_arg ();
          }
          else
          {
          ulong = __get_printf_int_arg ();
          }
        i = 0;
          do
          {
          ch = ulong % 8;			/* convert to ascii */
	  ulong /= 8;
          *cbuf-- = ch + '0';
          ++i;					/* increment digit count */
          }
          while (ulong != 0);
        ++cbuf;					/* back up one */
          if (prefix_flag)
          {
          __cond_pad (i, 1, precision_value, pad_flag,
				left_justify, &min_field, &result);
	  __printf_char ('0');
	  ++result;
          }
          else
          {
          __cond_pad (i, 0, precision_value, pad_flag,
				left_justify, &min_field, &result);
          }
        __output_str (i, cbuf, &precision_value, pad_flag,
				&min_field, &result);
      break;

      case 'c':
	++printf_ptr;
        ch = __get_printf_char_arg ();		/* get character */
          if (left_justify == 0)
          {
 	    while (min_field-- > 1)
	    {
	    __printf_char (' ');		/* left pad */
	    ++result;
	    }
          }
	__printf_char (ch);
	++result;
        --min_field;
          while (min_field-- > 0)
          {
	  __printf_char (' ');			/* right pad */
	  ++result;
          }
      break;

      case 's':
	++printf_ptr;
        conv_ptr = __get_printf_ptr_arg ();	/* get arg pointer */
        i = strlen (conv_ptr);			/* get string length */
          if (i > precision_value && precision_flag == 1)
          {
          i = precision_value;			/* use precision */
          }
          if (left_justify == 0)
          {
            while (min_field-- > i)
            {
	    __printf_char (' ');
	    ++result;
  	    }
          }
          while (*conv_ptr != '\0' && i > 0)
          {
	  __printf_char (*conv_ptr);
	  ++result;
          ++conv_ptr;
          --min_field;
          --i;					/* decrement precision */
          }
          while (min_field-- > 0)
          {
	  __printf_char (' ');
	  ++result;
          }
      break;

      case '%':
	++printf_ptr;
        --min_field;			/* account for percent sign */
	  if (pad_flag)
	  {
	  ch = '0';			/* zero pad */
	  }
	  else
	  {
	  ch = ' ';
	  }
          if (left_justify == 0)
          {
            while (min_field-- > 0)
            {
	    __printf_char (ch);
	    ++result;
            }
          }
	__printf_char ('%');
	++result;
          while (min_field-- > 0)
          {
	  __printf_char (ch);
	  ++result;
          }
      break;
      }
    }
  }
return (result);
}

