#include "stdlib.h"
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
*                A R C C O S I N E   F U N C T I O N                         *
*                                                                            *
*        U S E S    F L O A T S    I N S T E A D    O F   D O U B L E S      *
*****************************************************************************/

/*
#define DEBUG_MESSAGES  1
*/

extern const float f_pi, f_two_pi, f_pi_4;	 /* pi */
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
float acos_sum = 0.0;
float final_acos_sum = 4.712394;
float f_fabs ();
float f_acos ();

#ifndef INTERNAL
float *f_ptr;
int i;
char *conv_ptr;
char print_acos_sum = 1;
#endif

printf ("'f_acos' test\n");
for (k = -f_two_pi; k < 18.0; k += f_pi_4)
  {
  printf (".");
  j = f_acos (k);
    
    if (j < HUGE)
    acos_sum += j;

#ifdef DEBUG_MESSAGES
#ifndef INTERNAL
  f_ptr = &j;
  conv_ptr = (char *) f_ptr;

    printf ("j-> %x", (*(conv_ptr + 0) & 0x00ff));
    printf (" %x", (*(conv_ptr + 1) & 0x00ff));
    printf (" %x", (*(conv_ptr + 2) & 0x00ff));
    printf (" %x", (*(conv_ptr + 3) & 0x00ff));
#endif
#endif

#ifndef INTERNAL
  if (print_acos_sum != 0)
  printf ("The acos of %20.15f = %20.15f\n", (double) k, (double) j);
#endif
  }
  
#ifndef INTERNAL
  if (print_acos_sum != 0)
  printf ("acos_sum == %.10e\n", (double) acos_sum);
#endif

  if (f_fabs (f_fabs (acos_sum) - f_fabs (final_acos_sum)) < (_float_precision * 1.0e2))
  printf ("Acos Test Passed\n");
  else
  printf ("\n*****************ERROR IN ACOS TEST\n");
}
*/


/* arccos = pi_2 - arctan (x / sqrt(1 - sqr (x))) */

float f_atan();
float f_sqrt();

float f_acos (x)
float x;
{
float result;

  if (x == -1.0)
  {
  return (f_pi);
  }
  else if (x == 1.0)
  {
  return (0.0);
  }
 
  if (sqr(x) > 1.0)
  {
  errno = EDOM;
  return (0.0);
  }
  else
  {
  result = (f_pi_2 - f_atan (x / f_sqrt (1.0 - sqr(x))));
    if ((result < 0.0) || (result > f_pi))
    {
    errno = ERANGE;
    return (HUGE);
    }
  return (result); 
  }
}


