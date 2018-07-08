#include "math.h"
#include "error.h"

#ifdef INTERNAL
#define printf internal_nf_printf
#endif

	.asm
	.linklist
	.symbols
	.endasm

/*****************************************************************************
*                A R C S I N E   F U N C T I O N                             *
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
double asin_sum = 0.0;
double final_asin_sum = 0.0;
double fabs ();
double asin ();
double *f_ptr;
int i;
char   *conv_ptr;
char print_asin_sum = 1;

  for (k = -two_pi; k < 18.0; k += pi_4)
  {

  j = asin (k);
    
    if (j < HUGE)
    asin_sum += j;

#ifdef DEBUG_MESSAGES
  f_ptr = &j;
  conv_ptr = (char *) f_ptr;

    for (i = 0; i != 8; i++)
    printf ("conv_ptr -> %x\n", (*(conv_ptr + i) & 0x00ff));
#endif

  if (print_asin_sum != 0)
  printf ("The asin of %f = %f\n", k, asin (k));
  }
  
  if (print_asin_sum != 0)
  printf ("asin_sum == %.40e\n", asin_sum);

  if (fabs (fabs(asin_sum) - fabs(final_asin_sum)) < 1.0e-13)
  printf ("Asin Test Passed\n");
  else
  printf ("\n*****************ERROR IN ASIN TEST\n");
}
*/

/* arcsin (x) = arctan (x / sqrt (1 - sqr (x))) */

double atan();
double sqrt();

double asin (x)
double x;
{
double result;

  if (x == -1.0)
  {
  return (-pi_2);
  }
  else if (x == 1.0)
  {
  return (pi_2);
  }

  if (sqr(x) > 1.0)
  {
  errno = EDOM;
  return (0.0);
  }
  else
  {
  result = (atan(x/sqrt(1.0-sqr(x))));
    if ((result < (-pi_2)) || (result > pi_2))
    {
    errno = ERANGE;
    return (HUGE);
    }
  return (result);
  }
}

