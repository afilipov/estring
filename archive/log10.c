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
*                      L O G   B A S E  T E N                                 *
*******************************************************************************

              log10 x = ln (x) / ln10                                        */ 


/*
#define DEBUG_MESSAGES  1
*/

extern const double pi, two_pi, pi_4;           /* pi */
extern const double pi_2;                       /* pi divided by 2 */
extern const double i_pi_2;                     /* inverse of pi_2 */
extern const double ln10;			/* natural log of 10 */

#ifdef INTERNAL
extern const double _double_precision;	 	/* result precision */
#else
extern double _double_precision;	 	/* result precision */
#endif

/*
main ()
{
double k, j = 0;
double log_sum = 0.0;
double final_log_sum = 8.753297104375565141e1;
double fabs ();
double log10 ();
double *f_ptr;
int i;
char   *conv_ptr;
char print_log_sum = 1;

  for (k = 0.0; k < 53.0; k = k + pi_4)
  {

  j = log10 (k);
    if (k > 0.0)
    {
    log_sum = log_sum + j;
    }

#ifdef DEBUG_MESSAGES
  f_ptr = &j;
  conv_ptr = (char *) f_ptr;

    for (i = 0; i != 8; i++)
    printf ("conv_ptr -> %x\n", (*(conv_ptr + i) & 0x00ff));
#endif

    if (print_log_sum != 0)
    {
    printf ("The log10  of %f = %.10f\n", k, log10 (k));
    printf ("log_sum == %.40e\n\n", log_sum);
    }
  }
  
  if (print_log_sum != 0)
  printf ("log_sum == %.40e\n", log_sum);

  if (fabs (log_sum - final_log_sum) < 1.0e-8)
  printf ("Log10 Test Passed\n");
  else
  printf ("\n*****************ERROR IN LOG10 TEST\n");
}
*/

double log10 (x)
double x;
{
double ln ();
  if (x <= 0.0)
  {
  errno = EDOM;
  return (-HUGE);
  }
return (ln (x) / ln10);
}


