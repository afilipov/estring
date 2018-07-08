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

/****************************************************************************
*    M A C L A U R I N   S E R I E S  F O R   E V A L U A T I N G   T H E   * 
*             E X P O N E N T I A L   F U N C T I O N                       *
*                                                                            *
*        U S E S    F L O A T S    I N S T E A D    O F   D O U B L E S      *
*****************************************************************************

              Copyright (C) 1986 by 2500 A.D. Software, Inc.
                                                  

   Power_i is a specialized power function which does a minimum amount of check-
   ing and evaluates a base 16 number to some integral exponent. The purpose 
   of this function is to make the function exp faster. */

#define LN16  2.77258872

/*
#define DEBUG_MESSAGES  1
*/

extern const float f_pi, f_two_pi, f_pi_4;      /* pi */
extern const float f_pi_2;                      /* pi divided by 2 */
extern const float f_i_pi_2;                    /* inverse of pi_2 */

#ifdef INTERNAL
extern const float _float_precision;	 	/* result precision */
#define  __f_exp1     __if_exp1
#define  __f_power_i  __if_power_i
#define  __f_power_r  __if_power_r
#else
extern float _float_precision;		 	/* result precision */
#endif

/*
main ()
{
float k, j;
float exp_sum = 0.0;
float final_exp_sum = 5.8670928e7;
float f_fabs ();
float f_exp ();
float __f_exp1 ();

#ifndef INTERNAL
float *f_ptr;
int i;
char *conv_ptr;
char print_exp_sum = 1;
#endif

#ifdef DEBUG_MESSAGES
printf ("'f_exp' Test\n");
#endif
  for (k = -f_two_pi; k < 18.0; k += f_pi_4)
  {
  printf (".");
  j = f_exp (k);
  exp_sum += j;

#ifdef DEBUG_MESSAGES
#ifndef INTERNAL
  f_ptr = &j;
  conv_ptr = (char *) f_ptr;
    for (i = 0; i != 4; i++)
    printf ("conv_ptr -> %x\n", (*(conv_ptr + i) & 0x00ff));
#endif
#endif

#ifndef INTERNAL
    if (print_exp_sum != 0)
    {
    printf ("The exp of %20.15f = %20.15f\n", (double) k, (double) j);
    printf ("The exp1 of %20.15f = %20.15f\n", (double) k, (double) (__f_exp1 (k)));
    }
#endif
  }
  
#ifndef INTERNAL
  if (print_exp_sum != 0)
  printf ("exp_sum == %.10e\n", (double) exp_sum);
#endif

  if (f_fabs (exp_sum - final_exp_sum) < (_float_precision * 1.0e11))
  printf ("Exp Test Passed\n");
  else
  printf ("\n*****************ERROR IN EXP TEST\n");
}
*/


float __f_power_i (x)
int x;
{
float result;

register  int count = iabs(x);
  if (x == 0.0)
  {
  return (1.0);
  }
  else
  {
    for (result = 1.0; count > 0; --count)
    {
    result = result * 16.0;
    }
    if (x < 0.0)
    {
    return (1.0 / result);
    }
  }
return (result);
}


/* Exp1 is a specialized function designed to evaluate the exponential function
   for a single precision argument.  The intent is to avoid unnessecary checks
   and work exclusively with the exp and power_r functions.  Note that the 
   only values that will ever be passed are positive. Any others will be trapped
   as errors before this function is ever called. */

float f_fabs ();

float __f_exp1 (arg)
float arg;
{
float fabs_term;
float sum = 1.0;
float term = 1.0;
float k = 0.0;

  if (arg == 0.0)
  {
  return (1.0);
  }
  else
  {
    do
    {
    term = term * (arg / (k+1.0));
    sum += term;
    k = k + 1;
    fabs_term = f_fabs(term);
    }
    while (fabs_term >= _float_precision);
  } 
return (sum);
}


/* Power_r is a specialized power function which does a minimum amount of check-
   ing and evaluates a base 16 number to some rational exponent. The purpose 
   of this function is to make the function exp faster. */

float __f_exp1 ();

float __f_power_r (n)
float n;
{
  if (n == 0.0)
  {
  return (1.0);
  }
  else
  {
  return (__f_exp1(n * (float) LN16));
  }
}


/* Exp evaluates the exponential function for a single precision argu-
   ment.  */

f_i_floor ();

float f_exp (arg)
float arg;
{
float z;

  if (arg == 0.0)
  {
  return (1.0);
  }
  else if (arg > LOGHUGE) 
  {
  errno = EDOM;
  return (HUGE);
  }
  else
  {
  float mantissa;
  float y;
  float __f_power_r (), result;
  float __f_power_i (), exponent;
  register int m;

  y = ((-arg) * (1.0 / LN16));
  m = f_i_floor(y);
  z = y - m;
  mantissa = __f_power_r (-z);         
  exponent = __f_power_i (-m);
  result = (mantissa * exponent);
    if (result > HUGE) 
    {
    errno = ERANGE;
    return (HUGE);
    } 
  return (result);
  }
}

