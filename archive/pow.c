#include "math.h"
#include "error.h"

#ifdef INTERNAL
#define printf internal_nf_printf
#endif

	.asm
	.linklist
	.symbols
	.endasm

/***************************************************************************
*                   GENERAL POWER FUNCTION                                 *
****************************************************************************

            Copyright (C) 1986 by 2500 A.D. Software, Inc.
                                                  
   This general power function takes two double floating point arguments,
   the first being the base and the second, the exponent. First all of the
   special cases, like base = 0 and exponent = 0, are checked. After these
   cases are eliminated, the sign of the base is checked.  If the base is
   negative, the exponent must be integral. If the function does not return
   after any of the special cases tests, the return value is calculated
   with the identity exp (exponent * ln (base)). */
  

/*
#define DEBUG_MESSAGES  1
*/

extern const double pi, two_pi, pi_4;           /* pi */
extern const double pi_2;                       /* pi divided by 2 */
extern const double i_pi_2;                     /* inverse of pi_2 */

#ifdef INTERNAL
extern const double _double_precision;	 	/* result precision */
#else
extern double _double_precision;	 	/* result precision */
#endif

/*
main ()
{
double k, j;
double pow_sum = 0.0;
double final_pow_sum = 9.468822377880278369e32;
double fabs ();
double pow ();
double *f_ptr;
int i, l = 0;
double t = 0.0;
char   *conv_ptr;
char print_pow_sum = 1;

t = -10.0;

  for (k = 0.0; k < 13.0; k = k + pi_4)
  {
  l = (int)t;
  j = pow (k, t);
    if ((fabs(t) - l == 0.0) && (t != 0.0))
    {
    pow_sum = pow_sum + j;
    }

#ifdef DEBUG_MESSAGES
  f_ptr = &j;
  conv_ptr = (char *) f_ptr;

    for (i = 0; i != 8; i++)
    printf ("conv_ptr -> %x\n", (*(conv_ptr + i) & 0x00ff));
#endif

    if (print_pow_sum != 0)
    {
    printf ("The pow of %f to the %f power = %.10e\n", k, t, pow (k,t));
    printf ("pow_sum == %.40e\n\n", pow_sum);
    }
  t += 2.5;
  }
  
  if (print_pow_sum != 0)
  printf ("pow_sum == %.40e\n", pow_sum);

  if (fabs (pow_sum - final_pow_sum) < 1.0e255)
  printf ("Power Test Passed\n");
  else
  printf ("\n*****************ERROR IN POWER TEST\n");
}
*/ 

double  pow (base,exponent)
double  base;
double  exponent;
{
double  fabs ();
double  result;
double  exp ();                
double  ln ();
int count = 0;
int temp = 0;

temp = (int)exponent;

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
  count = iabs(temp); 
    if ((fabs(exponent) - count) != 0.0)
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
        if ((fabs(result) < TINY) && (result != 0.0))
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
    count = iabs(temp); 
    goto int_exp;
    } 
  result = exp (exponent * ln (base));
    if (result > HUGE)
    {
    errno = ERANGE;
    return (HUGE);
    }
  return (result);  
  }
}

