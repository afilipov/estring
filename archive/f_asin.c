#include "math.h"
#include "error.h"

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

/*****************************************************************************
*                A R C S I N E   F U N C T I O N                             *
*                                                                            *
*        U S E S    F L O A T S    I N S T E A D    O F   D O U B L E S      *
*****************************************************************************/


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

/*
main ()
{
float k, j;
float asin_sum = 0.0;
float final_asin_sum = 0.0;
float f_asin ();

#ifndef INTERNAL
float *f_ptr;
int i;
char *conv_ptr;
char print_asin_sum = 0;
#endif

printf ("'f_asin' test\n");
  for (k = -f_two_pi; k < 18.0; k += f_pi_4)
  {
  printf (".");
  j = f_asin (k);
    
    if (j < HUGE)
    asin_sum += j;

#ifdef DEBUG_MESSAGES
#ifndef INTERNAL
  f_ptr = &j;
  conv_ptr = (char *) f_ptr;

    for (i = 0; i != 4; i++)
    printf ("conv_ptr -> %x\n", (*(conv_ptr + i) & 0x00ff));
#endif
#endif

#ifndef INTERNAL
  if (print_asin_sum != 0)
  printf ("The asin of %f = %f\n", (double) k, (double) j);
#endif
  }
  
#ifndef INTERNAL
  if (print_asin_sum != 0)
  printf ("asin_sum == %.10e\n", (double) asin_sum);
#endif

  if (f_fabs (f_fabs (asin_sum) - f_fabs (final_asin_sum)) < (_float_precision * 1.0e3))
  printf ("Asin Test Passed\n");
  else
  printf ("\n*****************ERROR IN ASIN TEST\n");
}
*/

/* arcsin (x) = arctan (x / sqrt (1 - sqr (x))) */

float f_sqrt ();
float f_atan ();

float f_asin (x)
float x;
{
float result;

  if (x == -1.0)
  {
  return (-f_pi_2);
  }
  else if (x == 1.0)
  {
  return (f_pi_2);
  }

  if (sqr(x) > 1.0)
  {
  errno = EDOM;
  return (0.0);
  }
  else
  {
  result = (f_atan (x / f_sqrt (1.0 - sqr(x))));
    if ((result < (-f_pi_2)) || (result > f_pi_2))
    {
    errno = ERANGE;
    return (HUGE);
    }
  return (result);
  }
}

