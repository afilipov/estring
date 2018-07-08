
#ifdef INTERNAL
#define __ns_icscanf __internal_ns_icscanf
#define __scanf_char __iscanf_char
#define __unget_scanf_char __iunget_scanf_char
#define __get_scanf_ptr_arg __iget_scanf_ptr_arg
#endif

#include "printf.h"

/******************************************************************************/
/* CHAR, INT & LONG SCANF WITHOUT SET MATCHING                                */
/******************************************************************************/

	.asm
	.linklist
	.symbols
	.endasm

char __scanf_char ();

__ns_icscanf (scanf_ptr)

#ifdef INTERNAL
const char *scanf_ptr;
#else
char *scanf_ptr;
#endif

{
char ch;
char suppression_flag;
char size_flag;
char neg_flag;

char *char_ptr1;

int result = 0;

int *int_ptr;

unsigned int count;
unsigned int max_field;

short *short_ptr;

unsigned long ulong;

long *long_ptr;

  while (*scanf_ptr != '\0')
  {
    if (*scanf_ptr != '%')
    {
    ch = __scanf_char ();
      if (*scanf_ptr == ' ' || *scanf_ptr == '\t' || *scanf_ptr == '\n')
      {
	while (*scanf_ptr == ' '
	    || *scanf_ptr == '\t'
	    || *scanf_ptr =='\n')
	{
	++scanf_ptr;				/* skip string whitespace */
	}
        while (ch == ' ' || ch == '\t' || ch == '\n')
	{
	ch = __scanf_char ();			/* skip input whitespace */
	}
      __unget_scanf_char (ch);			/* push back other */
      }
      else
      {
        if (*scanf_ptr != ch)			/* do characters match ? */
        {
        __unget_scanf_char (ch);		/* no, push it back */
	return (result);
        }
      ++scanf_ptr;				/* next string character */
      }
    }
    else
    {
    ++scanf_ptr;				/* point past % */
      if (*scanf_ptr == '*')			/* check suppression flag */
      {
      suppression_flag = 1;
      ++scanf_ptr;
      }
      else
      {
      suppression_flag = 0;
      }

    max_field = 0;
      while (*scanf_ptr >= '0' && *scanf_ptr <= '9')
      {
      max_field = (max_field * 10) + (*scanf_ptr - '0');
      ++scanf_ptr;
      } 

      if (*scanf_ptr == 'h')			/* check short flag */
      {
      size_flag = 1;
      ++scanf_ptr;
      }
      else if (*scanf_ptr == 'l')		/* check long flag */
      {
      size_flag = 2;
      ++scanf_ptr;
      }
      else
      {
      size_flag = 0;
      }
      
      switch (*scanf_ptr)			/* process conversions */
      {
      case 'x':
      case 'X':
	++scanf_ptr;
	ulong = 0l;
	  do
	  {
	  ch = __scanf_char ();			/* read character */
	  } while (ch == ' ' || ch == '\t' || ch == '\n');
        count = 0;
          while (ch != EOF)
          {
	    if (ch == '0')
            {
 	      if (count != 0)
	      {
	      ch -= '0';			/* check for leading 0 */
	      }
	      else
	      {
	      goto next_hex;
	      }
	    }
	    else if (ch >= '1' && ch <= '9')
	    {
            ch -= '0';				/* convert to hex */
            }
            else if (ch >= 'a' && ch <= 'f')
            {
	    ch -= 0x57;
            }
	    else if (ch >= 'A' && ch <= 'F')
	    {
	    ch -= 0x37;
	    }
	    else
	    {
	      if (ch == 'x' || ch == 'X')
	      {
	        if (count == 1)
	        {
	        goto next_hex;			/* check leading x or X */
	        }
	      }
	    __unget_scanf_char (ch);		/* push back 1 character */
	    break;				/* done if any other char */
	    }
	  ulong = (ulong * 16) + ch;
next_hex:
	  ++count;
	    if (count == max_field && max_field != 0)
	    {
	    break;
	    }
	  ch = __scanf_char ();			/* read next character */
          }
	goto store_value;
      break;

      case 'd': 
	++scanf_ptr;
	ulong = 0l;
	  do
	  {
          ch = __scanf_char ();			/* read character */
	  } while (ch == ' ' || ch == '\t' || ch == '\n');
        count = 0;
	  if (ch == '-')			/* negative ? */
	  {
	  neg_flag = 1;
	  ch = __scanf_char ();			/* read another character */
	  }
	  else
	  {
	  neg_flag = 0;
	    if (ch == '+')
	    {
	    ch = __scanf_char ();		/* read another character */
	    }
	  }
	  while (ch != EOF)
          {
	    if (ch >= '0' && ch <= '9')
	    {
	    ulong = (ulong * 10) + (ch - '0');	/* convert to decimal*/
	    ++count;				/* increment count */
	      if (count == max_field && max_field != 0)
	      {
	      break;				/* done */
	      }
	    }
	    else
	    {
	    __unget_scanf_char (ch);
	    break;
	    }
	  ch = __scanf_char ();			/* read next character */
	  }
	  if (neg_flag)
	  {
	  ulong = ~ulong + 1;			/* complement */
	  }
	goto store_value;
      break;

      case 'u': 
	++scanf_ptr;
	ulong = 0l;
	  do
	  {
          ch = __scanf_char ();			/* read character */
	  } while (ch == ' ' || ch == '\t' || ch == '\n');
        count = 0;
	  while (ch != EOF)
          {
	    if (ch >= '0' && ch <= '9')
	    {
	    ulong = (ulong * 10) + (ch - '0');	/* convert to decimal */
	    ++count;
	      if (count == max_field && max_field != 0)
	      {
	      break;
	      }
	    }
	    else
	    {
	    __unget_scanf_char (ch);		/* pushback character */
	    break;
	    }
	  ch = __scanf_char ();			/* read next character */
	  }
	goto store_value;
      break;

      case 'o':
	++scanf_ptr;
	ulong = 0l;
	  do
	  {
          ch = __scanf_char ();			/* read character */
	  } while (ch == ' ' || ch == '\t' || ch == '\n');
        count = 0;
          while (ch != EOF)
          {
	    if(ch >= '0' && ch <= '7')
	    {
	    ulong = (ulong * 8) + (ch - '0');	/* convert to octal */
	    ++count;
	      if (count == max_field && max_field != 0)
	      {
	      break;
	      }
            }
	    else
	    {
	    __unget_scanf_char (ch);		/* push back character */
	    break;
	    }
	  ch = __scanf_char ();			/* read next character */
          }
store_value:
	  if (suppression_flag == 0 && count != 0)
	  {
	  ++result;
	    if (size_flag == 1)
	    {
	    short_ptr = (short *) __get_scanf_ptr_arg ();
	    *short_ptr = (short) ulong;
	    }
	    else if (size_flag == 2)
	    {
	    long_ptr = (long *) __get_scanf_ptr_arg ();
	    *long_ptr = ulong;
	    }
	    else
	    {
	    int_ptr = (int *) __get_scanf_ptr_arg ();
	    *int_ptr = (int) ulong;
	    }
	  }
      break;

      case 'c':
	++scanf_ptr;
          if (suppression_flag == 0)		/* get argument pointer */
          {
          char_ptr1 = __get_scanf_ptr_arg ();
	  ++result;
	  }
        count = 0;
	  do
	  {
          ch = __scanf_char ();			/* read character */
	    if (suppression_flag == 0)
	    {
              if (ch != EOF)
              {
              *char_ptr1 = ch;			/* store character */
	      char_ptr1++;
              }
	      else
	      {
	      --result;
	      break;
	      }
	    }
	  ++count;
          } while (count < max_field);
      break;

      case 's':
	++scanf_ptr;
	  if(suppression_flag == 0)
          {
          char_ptr1 = __get_scanf_ptr_arg ();
	  ++result;
          }
	  do
	  {
          ch = __scanf_char ();
	  } while (ch == ' ' || ch == '\t' || ch == '\n');
	count = 0;
          while (ch != EOF)
          {
	    if(suppression_flag == 0)
	    {
            *char_ptr1 = ch;			/* store character */
	    ++char_ptr1;
	    }
	  ++count;
	    if (count == max_field)
	    {
	    break;
            }
          ch = __scanf_char ();
	    if (ch == '\t' || ch == ' ' || ch == '\n')
	    {
	    __unget_scanf_char (ch);		/* push back character */
	    break;
	    }
          }
	  if (suppression_flag == 0)
	  {
	  *char_ptr1 = '\0';			/* terminate */
	  }
      break;

      case '%':
	++scanf_ptr;
        ch = __scanf_char ();
	  if (ch != '%')
	  {
	  __unget_scanf_char (ch);
	  }
      break;
      }
    }
  }
return (result);
}

