#include "math.h"
#include "error.h"

/*
#ifdef INTERNAL

#define printf test_printf

printf (arg1)
const char *arg1;
{
  while (*arg1 != 0)
  {
  iputchar (*arg1++);
  }
}
#endif
*/

	.asm
	.linklist
	.symbols
	.endasm

/***************************************************************************
*                   GENERAL POWER FUNCTION                                 *
*                                                                          *
*      U S E S    F L O A T S    I N S T E A D    O F   D O U B L E S      *
****************************************************************************

            Copyright (C) 1986 by 2500 A.D. Software, Inc.
                                                  
   This general power function takes two single floating point arguments,
   the first being the base and the second, the exponent. First all of the
   special cases, like base = 0 and exponent = 0, are checked. After these
   cases are eliminated, the sign of the base is checked.  If the base is
   negative, the exponent must be integral. If the function does not return
   after any of the special cases tests, the return value is calculated
   with the identity exp (exponent * ln (base)). */
  

/*
#define DEBUG_MESSAGES  1
*/

extern const float f_pi, f_two_pi, f_pi_4;      /* pi */
extern const float f_pi_2;                      /* pi divided by 2 */
extern const float f_i_pi_2;                    /* inverse of pi_2 */

#ifdef INTERNAL
extern const float _float_precision;	 	/* result precision */
#else
extern float _float_precision;		 	/* result precision */
#endif

/*
main ()
{
float k, j;
float pow_sum = 0.0;
float final_pow_sum = 9.468851e32;
float f_fabs ();
float f_pow ();
int i, l = 0;
float t = 0.0;

#ifndef INTERNAL
float *f_ptr;
char *conv_ptr;
char print_pow_sum = 0;
#endif

printf ("'f_pow' Test\n");
t = -10.0;
  for (k = 0.0; k < 13.0; k = k + f_pi_4)
  {
  printf (".");
  l = (int) t;
  j = f_pow (k, t);
    if ((f_fabs (t) - l == 0.0) && (t != 0.0))
    {
    pow_sum = pow_sum + j;
    }

#ifdef DEBUG_MESSAGES
#ifndef INTERNAL
  f_ptr = &j;
  conv_ptr = (char *) f_ptr;
    for (i = 0; i != 4; i++)
    printf ("conv_ptr -> %x\n", (*(conv_ptr + i) & 0x00ff));
#endif
#endif

#ifndef INTERNAL
    if (print_pow_sum != 0)
    {
    printf ("The pow of %f to the %f power = %.10e\n", (double) k, (double) t, (double) j);
    printf ("pow_sum == %.10e\n\n", (double) pow_sum);
    }
#endif
  t += 2.5;
  }
  
#ifndef INTERNAL
  if (print_pow_sum != 0)
  printf ("pow_sum == %.10e\n", (double) pow_sum);
#endif

  if (f_fabs (pow_sum - final_pow_sum) < 1.0e28)
  printf ("Power Test Passed\n");
  else
  printf ("\n*****************ERROR IN POWER TEST\n");
}
*/

float  f_fabs ();
float  f_exp ();                
float  f_ln ();

float  f_pow (base,exponent)
float  base;
float  exponent;
{
float  result;
int count = 0;
int temp = 0;

temp = exponent;

  if ((exponent <= 0.0) && (base == 0.0))
  {
  errno = EDOM;
  return (HUGE);
  }
  else if ((base < 0.0) && ((exponent - temp) != 0.0))
  {
  errno = EDOM;
  return (-HUGE);
  }
  else if ((base == 0.0) && (exponent > 0.0))
  {
  return (0.0);
  }
  else if ((base != 0.0) && (exponent == 0.0))
  {
  return (1.0);
  }
  else if (base < 0.0)
  {
  count = iabs (temp); 
    if ((f_fabs (exponent) - count) != 0.0)
    {
    errno = EDOM;
    return (-HUGE);
    }
    else
    {
      int_exp:
      for (result = 1.0; count > 0; --count)
      {
      result = result * base;
      }
      if (exponent < 0.0)
      {
        if ((f_fabs (result) < TINY) && (result != 0.0))
        {
        errno = ERANGE;
        return (-TINY);
        }
      return (1.0 / result);
      }
      else
      {
        if (result > HUGE)
        {
        errno = ERANGE;
        return (HUGE);
        }
      return (result);
      } 
    }
  }
  else
  {
    if (exponent - (temp) == 0.0)
    {
    count = iabs (temp); 
    goto int_exp;
    } 
  result = f_exp (exponent * f_ln (base));
    if (result > HUGE)
    {
    errno = ERANGE;
    return (HUGE);
    }
  return (result);  
  }
}

