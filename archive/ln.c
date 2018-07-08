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
*             N A T U R A L     L O G    F U N C T I O N                    *
*****************************************************************************

              Copyright (C) 1986 by 2500 A.D. Software, Inc.
                                                  

   The natural log function is written in 2 parts. The function ln does 
   range reduction. Ln passes the reduced argument to ln1.  The double
   precision number returned by ln1 is used in conjuction with the
   variable temp to actually calculate the double returned by ln. */ 


#define LN16  2.772588722239781237       /* natural log of 16 */

extern int *exp_ptr;

/*
#define DEBUG_MESSAGES  1
*/

extern const double pi, two_pi, pi_4;           /* pi */
extern const double pi_2;                       /* pi divided by 2 */
extern const double i_pi_2;                     /* inverse of pi_2 */

#ifdef INTERNAL
extern const double _double_precision;	 	/* result precision */
#define  ln1  iln1
#else
extern double _double_precision;	 	/* result precision */
#endif

/*
main ()
{
double k, j;
double ln_sum = 0.0;
double final_ln_sum = 2.015521142708302e2;
double fabs ();
double ln ();
double ln1 ();
double *f_ptr;
int i;
char   *conv_ptr;
char print_ln_sum = 1;

  for (k = 0.0; k < 53.0; k = k + pi_4)
  {

  j = ln (k);
    if (k > 0.0)
    {
    ln_sum = ln_sum + j;
    }

#ifdef DEBUG_MESSAGES
  f_ptr = &j;
  conv_ptr = (char *) f_ptr;

    for (i = 0; i != 8; i++)
    printf ("conv_ptr -> %x\n", (*(conv_ptr + i) & 0x00ff));
#endif

    if (print_ln_sum != 0)
    {
    printf ("The ln  of %f = %.10f\n", k, ln (k));
    printf ("The ln1 of %f = %.10f\n", k, ln1 (k));
    printf ("ln_sum == %.40e\n\n", ln_sum);
    }
  }
  
  if (print_ln_sum != 0)
  printf ("ln_sum == %.40e\n", ln_sum);

  if (fabs (ln_sum - final_ln_sum) < 1.0e-8)
  printf ("Ln Test Passed\n");
  else
  printf ("\n*****************ERROR IN LN TEST\n");
}
*/


double ln1 (x)
double x;
{
double temp_term = 0;
double part1;
double part2 = 2.0;
double num = (x-1.0);
double denom = (x+1.0);
double fraction = (num/denom);
double term = (2.0*fraction);
double sqrfrac = sqr(fraction);
double sum = term;
int j = 1;

  if (x <= 0.0)
  {
  errno = EDOM;
  return (-HUGE);
  }
  else
  {
    do
    {
    part1 = term / part2;
    part2 = (2.0 / (2.0 * j + 1.0));
    term = part2 * part1 * sqrfrac; 
    sum = sum + term;
    j++;  
    temp_term = term;
    }
    while (temp_term > (_double_precision * 1.0e2));
  }
return (sum);
}


double ln (x)
double x;
{
double term = 0.0;
double ln1 ();              
double sum = 0.0;
double e = 0.0;
double m = 0.0;
double z = 0.0;
double temp = 0.0;
double frexp ();
double result = 0.0;
int exponent = 0;
int *p;

p = &exponent;
  if (x <= 0.0)
  {
  errno = EDOM;
  return (-HUGE);
  }

  if ((x < 20.0) && (x > 1.0))
  {
  result = ln1 (x);
  return (result);
  }

m = frexp (x, p);
z = ((m-0.25) / (m+0.25));
e = *p;
e = e * 0.25;
x = ((1.0+z)/(1.0-z));
temp = (e-0.5)*LN16;
sum = ln1 (x);
return (temp + sum);
}

