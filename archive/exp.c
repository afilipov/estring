#include "math.h"
#include "error.h"

#ifdef INTERNAL
#define printf internal_nf_printf
#endif

	.asm
	.linklist
	.symbols
	.endasm

/****************************************************************************
*    M A C L A U R I N   S E R I E S  F O R   E V A L U A T I N G   T H E   * 
*             E X P O N E N T I A L   F U N C T I O N                       *
*****************************************************************************

              Copyright (C) 1986 by 2500 A.D. Software, Inc.
                                                  

   Power_i is a specialized power function which does a minimum amount of check-
   ing and evaluates a base 16 number to some integral exponent. The purpose 
   of this function is to make the function exp faster. */

#define LN16  2.772588722239781237

#define DEBUG_MESSAGES  1

extern const double pi, two_pi, pi_4;           /* pi */
extern const double pi_2;                       /* pi divided by 2 */
extern const double i_pi_2;                     /* inverse of pi_2 */

#ifdef INTERNAL
extern const double _double_precision;	 	/* result precision */
#define  exp1     iexp1
#define  __power_i  __ipower_i
#define  __power_r  __ipower_r
#else
extern double _double_precision;	 	/* result precision */
#endif

/*
main ()
{
double k, j;
double exp_sum = 0.0;
double final_exp_sum = 5.867075195969799161e7;
double fabs ();
double exp ();
double __exp1 ();
double *f_ptr;
int i;
char   *conv_ptr;
char print_exp_sum = 1;

  for (k = -two_pi; k < 18.0; k += pi_4)
  {

  j = exp (k);
  exp_sum += j;
#ifdef DEBUG_MESSAGES
  f_ptr = &j;
  conv_ptr = (char *) f_ptr;

    for (i = 0; i != 8; i++)
    printf ("conv_ptr -> %x\n", (*(conv_ptr + i) & 0x00ff));
#endif

    if (print_exp_sum != 0)
    {
    printf ("The exp of %f = %f\n", k, exp (k));
    printf ("The exp1 of %f = %f\n", k, __exp1 (k));
    }
  }
  
  if (print_exp_sum != 0)
  printf ("exp_sum == %.40e\n", exp_sum);

  if (fabs (exp_sum - final_exp_sum) < 1.0e-5)
  printf ("Exp Test Passed\n");
  else
  printf ("\n*****************ERROR IN EXP TEST\n");
}
*/

double __power_i (x)
int x;
{
double result;
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
   for a double precision argument.  The intent is to avoid unnessecary checks
   and work exclusively with the exp and power_r functions.  Note that the 
   only values that will ever be passed are positive. Any others will be trapped
   as errors before this function is ever called. */

double __exp1 (arg)
double arg;
{
double fabs ();
double fabs_term;
double sum = 1.0;
double term = 1.0;
double k = 0.0;
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
    fabs_term = fabs(term);
    }
    while (fabs_term >= (_double_precision * 1.0e1));
  } 
return (sum);
}


/* Power_r is a specialized power function which does a minimum amount of check-
   ing and evaluates a base 16 number to some rational exponent. The purpose 
   of this function is to make the function exp faster. */

double __power_r (n)
double n;
{
double __exp1 ();

  if (n == 0.0)
  {
  return (1.0);
  }
  else
  {
  return (__exp1(n*LN16));
  }
}


/* Exp evaluates the exponential function for a double precision argu-
   ment.  */

double exp (arg)
double arg;
{
double z;
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
  double mantissa;
  double y;
  double __power_r (), result;
  double __power_i (), exponent;
  register int m;

  y = ((-arg) * (1.0 / LN16));
  m = i_floor(y);
  z = y - m;
  mantissa = __power_r (-z);         
  exponent = __power_i (-m);
  result = (mantissa * exponent);
    if (result > HUGE) 
    {
    errno = ERANGE;
    return (HUGE);
    } 
  
  return (result);
  }
}

