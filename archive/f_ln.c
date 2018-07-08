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
*             N A T U R A L     L O G    F U N C T I O N                    *
*                                                                           *
*       U S E S    F L O A T S    I N S T E A D    O F   D O U B L E S      *
*****************************************************************************

              Copyright (C) 1986 by 2500 A.D. Software, Inc.
                                                  

   The natural log function is written in 2 parts. The function ln does 
   range reduction. Ln passes the reduced argument to ln1.  The single
   precision number returned by ln1 is used in conjuction with the
   variable temp to actually calculate the float returned by ln. */ 


#define LN16  2.77258872	       /* natural log of 16 */

extern int *exp_ptr;

/*
#define DEBUG_MESSAGES  1
*/

extern const float f_pi, f_two_pi, f_pi_4;      /* pi */
extern const float f_pi_2;                      /* pi divided by 2 */
extern const float f_i_pi_2;                    /* inverse of pi_2 */

#ifdef INTERNAL
extern const float _float_precision;	 	/* result precision */
#define  f_ln1  if_ln1
#else
extern float _float_precision;		 	/* result precision */
#endif

/*
main ()
{
float k, j;
float ln_sum = 0.0;
float final_ln_sum = 2.01552e2;
float f_fabs ();
float f_ln ();
float f_ln1 ();

#ifndef INTERNAL
float *f_ptr;
int i;
char *conv_ptr;
char print_ln_sum = 1;
#endif

printf ("'f_ln' Test\n");
  for (k = 0.0; k < 53.0; k = k + f_pi_4)
  {
  printf (".");
  j = f_ln (k);
    if (k > 0.0)
    {
    ln_sum = ln_sum + j;
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
    if (print_ln_sum != 0)
    {
    printf ("The ln  of %f = %.10f\n", (double) k, (double) j);
    printf ("The ln1 of %f = %.10f\n", (double) k, (double) j);
    printf ("ln_sum == %.10e\n\n", (double) ln_sum);
    }
#endif
  }
  
#ifndef INTERNAL
  if (print_ln_sum != 0)
  printf ("ln_sum == %.10e\n", (double) ln_sum);
#endif

  if (f_fabs (ln_sum - final_ln_sum) < (_float_precision * 1.0e4))
  printf ("Ln Test Passed\n");
  else
  printf ("\n*****************ERROR IN LN TEST\n");
}
*/


float f_ln1 (x)
float x;
{
float temp_term = 0;
float part1;
float part2 = 2.0;
float num = (x-1.0);
float denom = (x+1.0);
float fraction = (num/denom);
float term = (2.0*fraction);
float sqrfrac = sqr(fraction);
float sum = term;
int j = 1;

#ifdef DEBUG_MESSAGES
printf ("num = %f, denom = %f, fraction = %f, term = %f, sqrfrac = %f\n", (double) num, (double) denom, (double) fraction, (double) term, (double) sqrfrac);
#endif

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

#ifdef DEBUG_MESSAGES
printf ("part1 = %f, part2 = %f, term = %f, sum = %f\n", (double) part1, (double) part2, (double) term, (double) sum);
#endif

    }
    while (temp_term > _float_precision);
  }
return (sum);
}

float f_frexp ();
float f_ln1 ();              

float f_ln (x)
float x;
{
float term = 0.0;
float sum = 0.0;
float e = 0.0;
float m = 0.0;
float z = 0.0;
float temp = 0.0;
float result = 0.0;
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
  result = f_ln1 (x);
  return (result);
  }

m = f_frexp (x, p);
z = ((m-0.25) / (m+0.25));
e = *p;
e = e * 0.25;
x = ((1.0+z)/(1.0-z));
temp = (e-0.5)*LN16;
sum = f_ln1 (x);

#ifdef DEBUG_MESSAGES
printf ("m = %f, z = %f, e = %f, x = %f, temp = %f, sum = %f\n", (double) m, (double) z, (double) e, (double) x, (double) temp, (double) sum);
#endif

return (temp + sum);
}

