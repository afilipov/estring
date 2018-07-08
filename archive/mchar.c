
	.asm
	.linklist
	.symbols
	.endasm

#ifdef INTERNAL
#define __icscanf __internal_icscanf
#define __match_char __internal_match_char
#define __store_value __internal_store_value
#define __scanf_char __iscanf_char
#define __unget_scanf_char __iunget_scanf_char
#define __get_scanf_ptr_arg __iget_scanf_ptr_arg
#endif

#include "printf.h"

char __scanf_char ();
void __unget_scanf_char ();

void __match_char (start, end, dest, max_ch, result_ptr, neg_flag)
#ifdef INTERNAL
far char *start;
far char *end;
char *dest;
int  max_ch;
int  *result_ptr;
char neg_flag;
#else
char *start;
char *end;
char *dest;
int  max_ch;
int  *result_ptr;
char neg_flag;
#endif
{
char match;
char ch;

#ifdef INTERNAL
far char *ptr;
#else
char *ptr;
#endif

match = 0;					/* no matches yet */
  while(1)
  {
  ch = __scanf_char();				/* get next character */
    if(ch == EOF)				/* end of file ? */
    {
      if(match)
      {
      (*result_ptr)++;				/* increment result */
      }
    return;					/* done */
    }
    for(ptr = start;ptr < end;ptr++)
    {
      if(ch == *ptr)
      {
      break;					/* search set for ch */
      }
    }
    if(neg_flag)				/* negate flag set ? */
    {
      if(ptr < end)
      {
      break;					/* ch was in set */
      }
    }
    else if(ptr >= end)
    {
    break;					/* ch not in set */
    }
  --max_ch;					/* decrement character count */
    if(dest != (char *) 0)
    {
    match = 1;					/* match */
    *dest++ = ch;				/* store ch */
    }
    if(max_ch == 0)
    {
    break;					/* max characters read */
    }
  }
  if(dest != (char *) 0)
  {
  (*result_ptr)++;				/* successful */
  *dest = '\0';
  }
__unget_scanf_char(ch);				/* push back character */
}


