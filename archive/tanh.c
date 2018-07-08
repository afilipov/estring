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
*                  T A N H   F U N C T I O N                                  *
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
double tanh_sum = 0.0;
double final_tanh_sum = 1.399999816960453280e1;
double fabs ();
double tanh ();
double *f_ptr;
int i;
char   *conv_ptr;
char print_tanh_sum = 1;

  for (k = -two_pi; k < 18.0; k += pi_4)
  {

  j = tanh (k);
  tanh_sum += j;
#ifdef DEBUG_MESSAGES
printf ("\nDifference is %.40e\n", fabs(tanh_sum - final_tanh_sum));
  f_ptr = &j;
  conv_ptr = (char *) f_ptr;

    for (i = 0; i != 8; i++)
    printf ("conv_ptr -> %x\n", (*(conv_ptr + i) & 0x00ff));
#endif

  if (print_tanh_sum != 0)
  printf ("The tanh of %f = %f\n", k, tanh (k));
  }
  
  if (print_tanh_sum != 0)
  {
  printf ("tanh_sum == %.40e\n", tanh_sum);
  printf ("final_tanh_sum == %.40e\n", final_tanh_sum);
  }

  if (fabs (tanh_sum - final_tanh_sum) < 1.0e-6)
  printf ("Tanh Test Passed\n");
  else
  printf ("\n*****************ERROR IN TANH TEST\n");
}
*/

double tanh (radians)
double radians;
{
double sqrt ();
double sinh ();
double sinhh;

sinhh = sinh (radians);
return (sinhh / sqrt(1.0 + sqr(sinhh)));
}

