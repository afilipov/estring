
	.asm
	.linklist
	.symbols
	.endasm

#ifdef INTERNAL
#define __icscanf __internal_icscanf
#define __scanf_char __iscanf_char
#define __unget_scanf_char __iunget_scanf_char
#define __get_scanf_ptr_arg __iget_scanf_ptr_arg
#define __store_value __internal_store_value
#define __match_char __internal_match_char
#endif

#include "printf.h"

char *__get_scanf_ptr_arg ();

void __store_value (value, scanf_arg_ptr, result_ptr, suppression_flag, short_flag, long_flag)
long value;
char *scanf_arg_ptr;
int  *result_ptr;
char suppression_flag;
char short_flag;
char long_flag;
{
int   *int_scanf_arg_ptr;
short int *short_scanf_arg_ptr;
long  int *long_scanf_arg_ptr;

  if (suppression_flag == 0)
  {
  scanf_arg_ptr = __get_scanf_ptr_arg ();
    if (short_flag != 0)
    {
    short_scanf_arg_ptr = (short *) scanf_arg_ptr;
    *short_scanf_arg_ptr = (short) value;
    }
    else
    {
      if (long_flag != 0)
      {
      long_scanf_arg_ptr = (long *) scanf_arg_ptr;
      *long_scanf_arg_ptr = value;
      }
      else
      {
      int_scanf_arg_ptr = (int *) scanf_arg_ptr;
      *int_scanf_arg_ptr = (int) value;
      }
    }
  (*result_ptr)++;
  }
}

