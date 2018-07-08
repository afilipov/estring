#include "c6809io.h"
#include "math.h"
#include "error.h"

/* Uncomment the following to enable series term printf's */

/*
#define SERIES_TERMS
#define DEBUG_MESSAGES  1
*/

/*
#ifdef INTERNAL

#define printf test_printf

test_printf (arg1)
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
*   T A Y L O R  S E R I E S  A P P R O X A M A T I O N  F O R  S I N E       *
*                                                                             *
*         U S E S    F L O A T S    I N S T E A D    O F   D O U B L E S      *
*******************************************************************************

              Copyright (C) 1986 by 2500 A.D. Software, Inc.
                                                  
   This Taylor series approximation for the sine function takes a float argu-
   ment which must be given in radians.  First the argument is transformed by
   range reduction.  Then the transformed argument is used in a DO loop to
   generate terms of the series.  The generation of terms is made more 
   efficient by the use of nested multiplication.  When the last term 
   generated by the series is less than the desired accuracy, the loop 
   terminates, and the function returns a single precision floating point
   number. */ 

extern const float f_pi, f_two_pi, f_pi_4;       /* pi */
extern const float f_pi_2;                       /* pi divided by 2 */
extern const float f_i_pi_2;                     /* inverse of pi_2 */

#ifdef INTERNAL
extern const float _float_precision;	 	/* result precision */
#else
extern float _float_precision;		 	/* result precision */
#endif

float f_fabs ();

/*
main ()
{
float k, j;
float sin_sum = 0.0;
float final_sin_sum = 0.70710241;
float f_sin ();

#ifndef INTERNAL
float *f_ptr;
int i;
char *conv_ptr;
char print_sin_sum = 1;
#endif

printf ("'f_sin' Test\n");
  for (k = -f_two_pi; k < 18.0; k += f_pi_4)
  {
printf (".");
  j = f_sin (k);
  sin_sum += j;

#ifdef DEBUG_MESSAGES
#ifndef INTERNAL
/*
  f_ptr = &j;
  conv_ptr = (char *) f_ptr;

    for (i = 0; i != 4; i++)
    printf ("conv_ptr -> %x\n", (*(conv_ptr + i) & 0x00ff));
*/
#endif
#endif

#ifndef INTERNAL
  if (print_sin_sum != 0)
  printf ("The sin of %f = %f. sin_sum = %f\n", (double) k, (double) j, (double) sin_sum);
#endif
  }
  
#ifndef INTERNAL
  if (print_sin_sum != 0)
  printf ("sin_sum == %.10e\n", (double) sin_sum);
#endif

  if (f_fabs (sin_sum - final_sin_sum) < (_float_precision * 1.0e3))
  {
  printf ("Sin Test Passed\n");
  }
  else
  {
  printf ("\n*****************ERROR IN SIN TEST\n");
  }
}
*/


float f_sin (radians)
float radians;
{
int k;
int temp1 = 0;
float term;
float temp2;
float sum;
float u;
float temp;
float v;

  if (radians > HUGE) 
  {
  errno = EDOM;
  return (HUGE);
  }

u = f_i_pi_2 * radians;
temp = 0.25 * (u + 1.0);                  	/* reduce the argument */
temp1 = f_i_floor (temp);
v = u - ((float) 4.0 * temp1);
  if (v <= 1.0)
  {
  radians = v;
  }
  else
  {
  radians = 2.0 - v;
  }

radians *= f_pi_2;
sum = radians;             /* set sum and term to the first term value */
term = radians;            /* this eliminates the need to calculate the */
k = 1;                     /* first term */ 

/* HERE FOR THE SERIES GENERATION */

  do
  {
  temp2 = (float) 2.0 * k;
  term  = (-term * sqr(radians)) / ((temp2) * (temp2 + 1.0));
  sum += term;
  k++;

#ifdef SERIES_TERMS
printf ("temp2 = %f, term = %f, sum = %f, k = %f\n", (double) temp2, (double) term, (double) sum, (double) k);
#endif

  }
  while (f_fabs (term) >= (_float_precision * 1.0e-2));

  if (f_fabs (sum) > ((_float_precision * 5.0e4) + 1.0))
  {
  errno = ERANGE;
  return (HUGE);
  }
  
  if (f_fabs (sum) < _float_precision)
  {
  return (0.0);
  }

return (sum);
}
