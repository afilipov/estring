#include "math.h"
#include "error.h"

/*
#ifdef INTERNAL
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

/*****************************************************************************

                             C O S I N E

              Copyright (C) 1986 by 2500 A.D. Software, Inc.
                                                  
   This Taylor series approximation for the cosine function takes a double 
   argument which must be given in radians. This function uses the identity
   cos x = sin (pi_2 - x).  Returns a double precision argument. 

*******************************************************************************/

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
double cos_sum = 0.0;
double fabs ();
double sin (), cos ();

#ifndef INTERNAL
double *f_ptr;
int i;
char   *conv_ptr;
char print_cos_sum = 1;
#endif

printf ("Cos Test\n");
  for (k = -two_pi; k < 18.0; k += pi_4)
  {
  j = cos (k);
  cos_sum += j;
printf (".");

#ifdef DEBUG_MESSAGES
#ifndef INTERNAL
/*
  f_ptr = &j;
  conv_ptr = (char *) f_ptr;
    for (i = 0; i != 8; i++)
    printf ("conv_ptr -> %x\n", (*(conv_ptr + i) & 0x00ff));
*/
#endif
#endif

#ifndef INTERNAL
  if (print_cos_sum != 0)
  printf ("The cos of %f = %f\n", k, j);
#endif

#ifndef INTERNAL
  if (print_cos_sum != 0)
  printf ("cos_sum == %.40e\n", cos_sum);
#endif
  }

  if (fabs (fabs (cos_sum) - fabs (-0.7071067811865443531)) < 1.0e-13)
  printf ("Cos Test Passed\n");
  else
  printf ("\n*****************ERROR IN COS TEST\n");
}
*/


double cos (radians)
double radians;
{
double fabs ();
double sin ();

  if (radians > HUGE) 
  {
  errno = EDOM;
  return (HUGE);
  }

radians = sin (pi_2 - radians);

#ifdef DEBUG_MESSAGES
printf ("radians = %f\n", radians);
#endif

  if (fabs (radians) > ((_double_precision * 5.0e3) + 1.0))
  {
  errno = ERANGE;
  return (HUGE);
  }

  if (fabs (radians) < 1.0e-13)
  {
  return (0.0);
  }

return (radians);
}

