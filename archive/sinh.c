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
*   T A Y L O R  S E R I E S  A P P R O X A M A T I O N  F O R  S I N H       *
******************************************************************************/

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
double sinh_sum = 0.0;
double final_sinh_sum = 2.933488385599066317e7;
double fabs ();
double sinh ();
double *f_ptr;
int i;
char   *conv_ptr;
char print_sinh_sum = 1;

  for (k = -two_pi; k < 18.0; k += pi_4)
  {

  j = sinh (k);
  sinh_sum += j;
#ifdef DEBUG_MESSAGES
printf ("\nDifference is %.40e\n", fabs(sinh_sum - final_sinh_sum));
  f_ptr = &j;
  conv_ptr = (char *) f_ptr;

    for (i = 0; i != 8; i++)
    printf ("conv_ptr -> %x\n", (*(conv_ptr + i) & 0x00ff));
#endif

  if (print_sinh_sum != 0)
  printf ("The sinh of %f = %f\n", k, sinh (k));
  }
  
  if (print_sinh_sum != 0)
  {
  printf ("sinh_sum == %.40e\n", sinh_sum);
  printf ("final_sinh_sum == %.40e\n", final_sinh_sum);
  }

  if (fabs (sinh_sum - final_sinh_sum) < 1.0e-5)
  printf ("Sinh Test Passed\n");
  else
  printf ("\n*****************ERROR IN SINH TEST\n");
}
*/


double sinh (radians)
double radians;
{
int k;
double term, sum;
double fabs ();

  if (fabs(radians) > HUGE)
  {
  errno = ERANGE;
  return (HUGE);
  }

sum = radians;
term = radians;
k = 1;                  
  do
  {
  term  = (term * sqr(radians)) / ((2.0 * k) * (2.0 *  k + 1.0));
  sum = sum + term;
  k++;
  }
  while (fabs(term) >= _double_precision);

  if (fabs(sum) > HUGE)
  {
  errno = ERANGE;
  return (HUGE);
  }
return (sum);
}

