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

/******************************************************************************
*              T A N G E N T  =  S I N E  /  C O S I N E                      *
*                                                                             *
*         U S E S    F L O A T S    I N S T E A D    O F   D O U B L E S      *
*******************************************************************************

             Copyright (C) 1986 by 2500 A.D. Software, Inc.
                                                  
   This function for tangent uses the identity tan = sin / cos to evaluate
   the tangent function for a given argument.  The argument must be of type 
   float and given in radians. */ 


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

float f_fabs ();
float f_sin ();
float f_cos ();

/*
main ()
{
float k, j;
float tan_sum = 0.0;
float final_tan_sum = -2.257795e2;
float f_tan ();

#ifndef INTERNAL
float *f_ptr;
int i;
char *conv_ptr;
char print_tan_sum = 1;
#endif

printf ("'f_tan' Test\n");
  for (k = -f_two_pi; k < 18.0; k += 1.0)
  {
  printf (".");
  j = f_tan (k);
    if (j < HUGE)
    tan_sum += j;

#ifdef DEBUG_MESSAGES
#ifndef INTERNAL
  f_ptr = &j;
  conv_ptr = (char *) f_ptr;
    for (i = 0; i != 4; i++)
    printf ("conv_ptr -> %x\n", (*(conv_ptr + i) & 0x00ff));
#endif
#endif

#ifndef INTERNAL
  if (print_tan_sum != 0)
  printf ("The tan of %f = %f\n", (double) k, (double) j);
#endif
  }
  
#ifndef INTERNAL
  if (print_tan_sum != 0)
  printf ("tan_sum == %.10e\n", (double) tan_sum);
#endif

  if (f_fabs (f_fabs(tan_sum) - f_fabs(final_tan_sum)) < (_float_precision * 1.0e7))
  printf ("Tan Test Passed\n");
  else
  printf ("\n*****************ERROR IN TAN TEST\n");
}
*/


float f_tan (radians)
float radians;
{
float cosine;
float result;

cosine = f_cos (radians);
  
  if (f_fabs (cosine) <= _float_precision)
  {
  errno = ERANGE;
  return (HUGE);
  }
  else
  {
  result = (f_sin (radians) / cosine);
    if (f_fabs (result) > HUGE)
    {
    errno = ERANGE;
    return (HUGE);
    }
  return (result);
  }
}

