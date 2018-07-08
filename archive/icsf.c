
#ifdef INTERNAL
#define __icscanf __internal_icscanf
#define __match_char __internal_match_char
#define __store_value __internal_store_value
#define __scanf_char __iscanf_char
#define __unget_scanf_char __iunget_scanf_char
#define __get_scanf_ptr_arg __iget_scanf_ptr_arg
#endif

#include "printf.h"

/******************************************************************************/
/* CHAR, INT & LONG SCANF                                                     */
/******************************************************************************/

	.asm
	.linklist
	.symbols
	.endasm

char __scanf_char ();
void __store_value ();
void __match_char ();

__icscanf (scanf_ptr)

#ifdef INTERNAL
const char *scanf_ptr;
#else
char *scanf_ptr;
#endif

{
char  c1;
char  c2;
char  i = 0;
char  match;
char  suppression_flag;
char  short_flag;
char  long_flag;
char  neg_flag;

#ifdef INTERNAL
far char  *sptr;
#else
char  *sptr;
#endif

char  *scanf_arg_ptr = (char *) 0;	/* initialize to get rid of warning */
int   result;
unsigned   max_field;
long  slong1;
unsigned long  ulong1;

result = EOF;
c1 = *scanf_ptr++;
  while (c1 != '\0')
  {
  match = 1;
  max_field = 0;
  suppression_flag = 0;
  short_flag = 0;
  long_flag = 0;
    if (c1 != '%')
    {
    c2 = __scanf_char();
      if(c1 == ' ' || c1 == '\t' || c1 == '\n')
      {
	while (*scanf_ptr == ' '
	    || *scanf_ptr == '\t'
	    || *scanf_ptr =='\n')
	{
	++scanf_ptr;			/* goto first non-whitespace char */
	}
        while (c2 == ' '
	    || c2 == '\t'
	    || c2 == '\n')
	{
	c2 = __scanf_char();		/* skip whitespace */
	}
      __unget_scanf_char(c2);		/* push back other */
      }
      else
      {
        if(c1 != c2)
        {
        __unget_scanf_char(c2);		/* push it back */
	return (result);
        }
      }
    }
    else
    {
    ulong1 = 0;
    slong1 = 0;
    c1 = *scanf_ptr++; 			/* Check for flags */
      while (match != 0)
      {
      match = 0;
 
	/* Check for '*'.  If present read in characters but don't access 
           pointer or store the characters which were read in.  */

        if(c1 == '*')
        {
        suppression_flag = 1;
        c1 = *scanf_ptr++;
        match = 1;
        }

	/* Check for a field width specifier */

        while (c1 >= '0' && c1 <= '9')
        {
        c1 = c1 - '0';
        max_field = (max_field * 10) + c1;
        c1 = *scanf_ptr++;
        match = 1;
        } 
  
  	/* Check for size specification */

        if (c1 == 'h')
        {
        short_flag = 1;
        c1 = *scanf_ptr++;
        match = 1;
        }
        else
        {
          if (c1 == 'l')
          {
          long_flag = 1;
          c1 = *scanf_ptr++;
          match = 1;
          }
        }
      }
      
  	/* Process actual conversion of input characters */

      switch (c1)
      {
      case 'x':
      case 'X':
        c1 = __scanf_char ();			/* Read First Character */
          while (c1 == ' ' || c1 == '\t' || c1 == '\n')
          {
          c1 = __scanf_char ();			/* Skip Leading Whitespace */
          }
        i = 0;
          while (c1 != EOF)
          {
	    if (c1 == '0')
            {
 	      if (i != 0)
	      {
	      c1 -= '0';			/* check for leading 0 */
	      }
	      else
	      {
	      goto next_hex;
	      }
	    }
	    else if (c1 >= '1' && c1 <= '9')
	    {
            c1 -= '0';				/* convert to hex */
            }
            else if (c1 >= 'a' && c1 <= 'f')
            {
	    c1 -= 0x57;
            }
	    else if (c1 >= 'A' && c1 <= 'F')
	    {
	    c1 -= 0x37;
	    }
	    else
	    {
	      if (c1 == 'x' || c1 == 'X')
	      {
	        if (i == 1)
	        {
	        goto next_hex;			/* check leading x or X */
	        }
	      }
	    __unget_scanf_char(c1);		/* push back 1 character */
	    break;				/* done if any other char */
	    }
	  ulong1 = (ulong1 << 4) | c1;
next_hex:
	  ++i;
	    if(i == max_field && max_field != 0)
	    {
	    break;
	    }
	  c1 = __scanf_char();			/* read next character */
          }
          if (i != 0)
          {
	  __store_value (ulong1, scanf_arg_ptr, &result, suppression_flag, short_flag, long_flag);
          }
      break;

      case 'd': 
	neg_flag = 0;				/* assume positive */
        c1 = __scanf_char ();			/* read first character */
          while (c1 == ' ' || c1 == '\t' || c1 == '\n')
          {
          c1 = __scanf_char();			/* skip leading whitespace */
          }
        i = 0;
	  if(c1 == '-')				/* negative ? */
	  {
	  neg_flag = 1;
	  c1 = __scanf_char();			/* read another character */
	  }
	  else
	  {
	    if(c1 == '+')
	    {
	    c1 = __scanf_char();		/* read another character */
	    }
	  }
	  while(c1 != EOF)
          {
	    if(c1 >= '0' && c1 <= '9')
	    {
	    c1 -= '0';				/* convert to bcd */
	    slong1 *= 10;			/* multiply by ten */
	    slong1 += c1;			/* add new digit */
	    }
	    else
	    {
	    __unget_scanf_char(c1);		/* pushback character */
	    break;
	    }
	  ++i;					/* increment count */
	    if(i == max_field && max_field != 0)
	    {
	    break;				/* done */
	    }
	  c1 = __scanf_char();			/* read next character */
	  }
	  if(neg_flag)
	  {
	  slong1 = -slong1;			/* negate value */
	  }
          if (i != 0)
          {
	  __store_value (slong1, scanf_arg_ptr, &result, suppression_flag, short_flag, long_flag);
          }
      break;

      case 'u': 
        c1 = __scanf_char ();			/* read first character */
          while (c1 == ' ' || c1 == '\t' || c1 == '\n')
          {
          c1 = __scanf_char();			/* skip leading whitespace */
          }
        i = 0;
	  while(c1 != EOF)
          {
	    if(c1 >= '0' && c1 <= '9')
	    {
	    c1 -= '0';				/* convert to bcd */
	    ulong1 *= 10;			/* multiply by ten */
	    ulong1 += c1;			/* add new digit */
	    }
	    else
	    {
	    __unget_scanf_char(c1);		/* pushback character */
	    break;
	    }
	  ++i;					/* increment count */
	    if(i == max_field && max_field != 0)
	    {
	    break;				/* done */
	    }
	  c1 = __scanf_char();			/* read next character */
	  }
          if (i != 0)
          {
	  __store_value (ulong1, scanf_arg_ptr, &result, suppression_flag, short_flag, long_flag);
          }
      break;

      case 'o':
        c1 = __scanf_char ();		/* Read First Character */
          while (c1 == ' ' || c1 == '\t' || c1 == '\n')
          {
          c1 = __scanf_char ();		/* Skip Leading Whitespace */
          }
        i = 0;
          while(c1 != EOF)
          {
	    if(c1 >= '0' && c1 <= '7')
	    {
            c1 -= '0';			/* convert to octal */
            }
	    else
	    {
	    __unget_scanf_char(c1);	/* push back 1 character */
	    break;			/* done if any other char */
	    }
	  ulong1 = (ulong1 << 3) | c1;
next_oct:
	  ++i;
	    if (max_field)
	    {
	      if (i == max_field)
	      {
	      break;
	      }
	    }
	  c1 = __scanf_char();		/* read next character */
          }
          if (i != 0)
          {
	  __store_value (ulong1, scanf_arg_ptr, &result, suppression_flag, short_flag, long_flag);
          }
      break;

      case 'c':
             if (max_field == 0)
             {
	     max_field = 1;
             }
             if (suppression_flag != 1)
             {
             scanf_arg_ptr = __get_scanf_ptr_arg ();
	     ++result;
	     }
           i = 0;
	     while (i != max_field)
	     {
             c1 = __scanf_char ();		/* read character */
	       if (suppression_flag == 0)
	       {
                 if (c1 != 0)
                 {
                 *scanf_arg_ptr = c1;		/* store character */
	         scanf_arg_ptr++;
                 }
	       }
	     ++i;
             }
           break;
      case 's':
	     if(suppression_flag == 0)
             {
             scanf_arg_ptr = __get_scanf_ptr_arg ();
	     ++result;
             }
           c1 = __scanf_char ();
             while (c1 == ' ' || c1 == '\t' || c1 == '\n')
             {
             c1 = __scanf_char();		/* skip leading whitespace */
             }
	   i = 0;
             while(c1 != EOF)
             {
	       if(suppression_flag == 0)
	       {
               *scanf_arg_ptr = c1;		/* store character */
	       ++scanf_arg_ptr;
	       }
	     ++i;
	       if(i == max_field)
	       {
	       break;
               }
             c1 = __scanf_char();
	       if(c1 == '\t' || c1 == ' ' || c1 == '\n')
	       {
	       __unget_scanf_char(c1);		/* push back character */
	       break;
	       }
             }
	     if(suppression_flag == 0)
	     {
	     *scanf_arg_ptr = '\0';		/* terminate */
	     }
           break;

      case '%':
        c1 = __scanf_char();
	  if(c1 != '%')
	  {
	  __unget_scanf_char(c1);
	  }
      break;

      case '[':
	neg_flag = 0;
	  if(*scanf_ptr == '^')			/* negate flag ? */
	  {
	  neg_flag = 1;
	  ++scanf_ptr;
	  }
          if (suppression_flag != 1)
          {
          scanf_arg_ptr = __get_scanf_ptr_arg ();
          }
	  else
	  {
	  scanf_arg_ptr = (char *) 0;
	  }
	  if(max_field == 0)
	  {
	  max_field = 0xffff;
	  }
	  for(sptr = scanf_ptr;*sptr != ']';++sptr)
	  {
	    if(*sptr == '\0')
	    {
	    goto no_set;
	    }
	  }
	__match_char (scanf_ptr, sptr, scanf_arg_ptr, max_field, &result, neg_flag);
	scanf_ptr = sptr + 1;
no_set:
      break;
      }
    }
  c1 = *scanf_ptr++;
  }
return(result);
}

