#include "c6809io.h"
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

/*****************************************************************************

                             C O S I N E

              Copyright (C) 1986 by 2500 A.D. Software, Inc.
                                                  
   This Taylor series approximation for the cosine function takes a double 
   argument which must be given in radians. This function uses the identity
   cos x = sin (pi_2 - x).  Returns a single precision argument. 

         U S E S    F L O A T S    I N S T E A D    O F   D O U B L E S
*******************************************************************************/

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

/*
main ()
{
float k, j;
float cos_sum = 0.0;
float final_cos_sum = -0.707103;
float f_cos ();

#ifndef INTERNAL
float *f_ptr;
int i;
char *conv_ptr;
char print_cos_sum = 1;
#endif

printf ("'f_cos' Test\n");
  for (k = -f_two_pi; k < 18.0; k += f_pi_4)
  {
  printf (".");
  j = f_cos (k);
  cos_sum += j;

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
/*
  if (print_cos_sum != 0)
  printf ("The cos of %20.15f = %20.15f\n", (double) k, (double) j);
*/
#endif
  }
  
#ifndef INTERNAL
  if (print_cos_sum != 0)
  printf ("cos_sum == %.10e\n", (double) cos_sum);
#endif

  if (f_fabs (f_fabs (cos_sum) - f_fabs (final_cos_sum)) < (_float_precision * 1.0e2))
  printf ("Cos Test Passed\n");
  else
  printf ("\n*****************ERROR IN COS TEST\n");
}
*/


float f_cos (radians)
float radians;
{
float sum; 

  if (radians > HUGE) 
  {
  errno = EDOM;
  return (HUGE);
  }

sum = f_sin (f_pi_2 - radians);

  if (f_fabs (sum) > ((_float_precision * 5.0e4) + 1.0))
  {
  errno = ERANGE;
  return (HUGE);
  }

  if (f_fabs(sum) < _float_precision) 
  {
  return (0.0);
  }

return (sum);
}

