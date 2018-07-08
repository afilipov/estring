#include "math.h"
#include "error.h"

#ifdef INTERNAL
#define printf internal_nf_printf
#endif

	.asm
	.linklist
	.symbols
	.endasm

/******************************************************************************
*              T A N G E N T  =  S I N E  /  C O S I N E                      *
*******************************************************************************

             Copyright (C) 1986 by 2500 A.D. Software, Inc.
                                                  
   This function for tangent uses the identity tan = sin / cos to evaluate
   the tangent function for a given argument.  The argument must be of type 
   double and given in radians. */ 


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
double tan_sum = 0.0;
double final_tan_sum = -2.257705748320765622e2;
double fabs ();
double tan ();
double *f_ptr;
int i;
char   *conv_ptr;
char print_tan_sum = 1;

  for (k = -two_pi; k < 18.0; k += 1.0)
  {

  j = tan (k);
    
    if (j < HUGE)
    tan_sum += j;

#ifdef DEBUG_MESSAGES
  f_ptr = &j;
  conv_ptr = (char *) f_ptr;

    for (i = 0; i != 8; i++)
    printf ("conv_ptr -> %x\n", (*(conv_ptr + i) & 0x00ff));
#endif

  if (print_tan_sum != 0)
  printf ("The tan of %f = %f\n", k, tan (k));
  }
  
  if (print_tan_sum != 0)
  printf ("tan_sum == %.40e\n", tan_sum);

  if (fabs (fabs(tan_sum) - fabs(final_tan_sum)) < 1.0e-10)
  printf ("Tan Test Passed\n");
  else
  printf ("\n*****************ERROR IN TAN TEST\n");
}
*/

double tan (radians)
double radians;
{
double sin (), cos ();
double cosine;
double result;
double fabs ();

cosine = cos (radians);
  
  if (fabs(cosine) <= (_double_precision * 1.0e3))
  {
  errno = ERANGE;
  return (HUGE);
  }
  else
  {
  result = (sin (radians) / cosine);
    if (fabs(result) > HUGE)
    {
    errno = ERANGE;
    return (HUGE);
    }
  return (result);
  }
}

