#include "math.h"
#include "error.h"
#include "stdlib.h"

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
*    T A Y L O R  S E R I E S  A P P R O X I M A T I O N  F O R  C O S H     *
*                                                                            *
*        U S E S    F L O A T S    I N S T E A D    O F   D O U B L E S      *
*****************************************************************************/

/*
#define DEBUG_MESSAGES  1
*/

extern const float f_pi, f_two_pi, f_pi_4;       /* pi */
extern const float f_pi_2;                       /* pi divided by 2 */
extern const float f_i_pi_2;                     /* inverse of pi_2 */

#ifdef INTERNAL
extern const float _float_precision;	 	/* result precision */
#else
extern float _float_precision;		 	/* result precision */
#endif

/*
main ()
{
float k, j;
float cosh_sum = 0.0;
float final_cosh_sum = 2.933589e7;
float f_fabs ();
float f_cosh ();

#ifndef INTERNAL
float *f_ptr;
int i;
char *conv_ptr;
char print_cosh_sum = 1;
#endif

printf ("'f_cosh' Test\n");
  for (k = -f_two_pi; k < 18.0; k += f_pi_4)
  {
  printf (".");
  j = f_cosh (k);
  cosh_sum += j;

#ifdef DEBUG_MESSAGES
#ifndef INTERNAL
/*
  f_ptr = &j;
  conv_ptr = (char *) f_ptr;

    printf ("j-> %x", (*(conv_ptr + 0) & 0x00ff));
    printf (" %x", (*(conv_ptr + 1) & 0x00ff));
    printf (" %x", (*(conv_ptr + 2) & 0x00ff));
    printf (" %x", (*(conv_ptr + 3) & 0x00ff));
*/
#endif
#endif

#ifndef INTERNAL
  if (print_cosh_sum != 0)
  printf ("The cosh of %f = %f\n", (double) k, (double) j);
#endif
  }
  
#ifndef INTERNAL
  if (print_cosh_sum != 0)
  {
  printf ("cosh_sum == %.10e\n", (double) cosh_sum);
  printf ("final_cosh_sum == %.10e\n", (double) final_cosh_sum);
  }
#endif

  if (f_fabs (cosh_sum - final_cosh_sum) < (_float_precision * 1.0e10))
  printf ("Cosh Test Passed\n");
  else
  printf ("\n*****************ERROR IN COSH TEST\n");

#ifdef DEBUG_MESSAGES
#ifndef INTERNAL
  f_ptr = &cosh_sum;
  conv_ptr = (char *) f_ptr;
    printf ("cosh_sum-> %x", (*(conv_ptr + 0) & 0x00ff));
    printf (" %x", (*(conv_ptr + 1) & 0x00ff));
    printf (" %x", (*(conv_ptr + 2) & 0x00ff));
    printf (" %x", (*(conv_ptr + 3) & 0x00ff));
#endif
#endif
}
*/
    
float f_fabs ();

float  f_cosh (radians)
float  radians;
{
int k;
float sum;
float term;

  if (f_fabs (radians) > HUGE)
  {
  errno = ERANGE;
  return (HUGE);
  }

k = 0;                  
sum = 1.0;
term = 1.0;                
  do
  {
  term  = (term * sqr(radians)) / (((float) 2.0 * k + (float) 2.0) * ((float) 2.0 * k + (float) 1.0));
  sum = sum + term;
  k++;
  }
  while (f_fabs (term) >= _float_precision);

  if (f_fabs (sum) > HUGE)
  {
  errno = ERANGE;
  return (HUGE);
  }

return (sum);
}

