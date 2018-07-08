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
*    T A Y L O R  S E R I E S  A P P R O X I M A T I O N  F O R  C O S H     *
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
double cosh_sum = 0.0;
double final_cosh_sum = 2.933586810370738804e7;
double fabs ();
double cosh ();
double *f_ptr;
int i;
char   *conv_ptr;
char print_cosh_sum = 0;

  for (k = -two_pi; k < 18.0; k += pi_4)
  {

  j = cosh (k);
  cosh_sum += j;

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

  if (print_cosh_sum != 0)
  printf ("The cosh of %f = %f\n", k, cosh (k));
  }
  
  if (print_cosh_sum != 0)
  {
  printf ("cosh_sum == %.40e\n", cosh_sum);
  printf ("final_cosh_sum == %.40e\n", final_cosh_sum);
  }

  if (fabs (cosh_sum - final_cosh_sum) < 1.0e-6)
  printf ("Cosh Test Passed\n");
  else
  printf ("\n*****************ERROR IN COSH TEST\n");

#ifdef DEBUG_MESSAGES
  f_ptr = &cosh_sum;
  conv_ptr = (char *) f_ptr;

    printf ("cosh_sum-> %x", (*(conv_ptr + 0) & 0x00ff));
    printf (" %x", (*(conv_ptr + 1) & 0x00ff));
    printf (" %x", (*(conv_ptr + 2) & 0x00ff));
    printf (" %x", (*(conv_ptr + 3) & 0x00ff));
    printf (" %x", (*(conv_ptr + 4) & 0x00ff));
    printf (" %x", (*(conv_ptr + 5) & 0x00ff));
    printf (" %x", (*(conv_ptr + 6) & 0x00ff));
    printf (" %x\n", (*(conv_ptr + 7) & 0x00ff));
#endif

}
*/
    
double  cosh (radians)
double  radians;
{
int k;
double sum;
double fabs ();
double term;

  if (fabs(radians) > HUGE)
  {
  errno = ERANGE;
  return (HUGE);
  }

k = 0;                  
sum = 1.0;
term = 1.0;                
  do
  {
  term  = (term * sqr(radians)) / ((2.0 * k + 2) * (2.0 * k + 1.0));
  sum = sum + term;
  k++;
  }
  while (fabs(term) >= (_double_precision * 1.0e1));

  if (fabs(sum) > HUGE)
  {
  errno = ERANGE;
  return (HUGE);
  }

return (sum);
}

