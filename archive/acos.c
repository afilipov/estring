#include "math.h"
#include "error.h"
#include "stdlib.h"

#ifdef INTERNAL
#define printf internal_nf_printf
#endif

	.asm
	.linklist
	.symbols
	.endasm

/*****************************************************************************
*                A R C C O S I N E   F U N C T I O N                         *
*****************************************************************************/

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
double acos_sum = 0.0;
double final_acos_sum = 4.712388980384689674;
double fabs ();
double acos ();
double *f_ptr;
char   *conv_ptr;
char print_acos_sum = 1;

for (k = -two_pi; k < 18.0; k += pi_4)
  {
  printf ("k = %d\n", (int) k);

  j = acos (k);
    
    if (j < HUGE)
    acos_sum += j;

#ifdef DEBUG_MESSAGES

  f_ptr = &j;
  conv_ptr = (char *) f_ptr;

    printf ("j-> %x", (*(conv_ptr + 0) & 0x00ff));
    printf (" %x", (*(conv_ptr + 1) & 0x00ff));
    printf (" %x", (*(conv_ptr + 2) & 0x00ff));
    printf (" %x", (*(conv_ptr + 3) & 0x00ff));
    printf (" %x", (*(conv_ptr + 4) & 0x00ff));
    printf (" %x", (*(conv_ptr + 5) & 0x00ff));
    printf (" %x", (*(conv_ptr + 6) & 0x00ff));
    printf (" %x\n", (*(conv_ptr + 7) & 0x00ff));

#endif

  if (print_acos_sum != 0)
  printf ("The acos of %f = %f\n", k, j);

  if (print_acos_sum != 0)
  printf ("acos_sum == %.40e\n", acos_sum);
  }
  
  if (fabs (fabs(acos_sum) - fabs(final_acos_sum)) < 1.0e-13)
  printf ("Acos Test Passed\n");
  else
  printf ("\n*****************ERROR IN ACOS TEST\n");
}
*/


/* arccos = pi_2 - arctan (x / sqrt(1 - sqr (x))) */

double acos (x)
double atan();
double sqrt();

double x;
{
double result;

  if (x == -1.0)
  {
  return (pi);
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
  result = (pi_2 - atan(x/sqrt(1.0-sqr(x))));

#ifdef DEBUG_MESSAGES
printf ("result = %g\n", result);
#endif

    if ((result < 0.0) || (result > pi))
    {
    errno = ERANGE;
    return (HUGE);
    }
  return (result); 
  }
}


