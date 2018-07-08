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
*          S E R I E S  F O R  A R C T A N G E N T                           *
*****************************************************************************/

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
double atan_sum = 0.0;
double final_atan_sum = 2.075637760142613786e1;
double fabs ();
double atan ();
double *f_ptr;
int i;
char   *conv_ptr;
char print_atan_sum = 0;

  for (k = -two_pi; k < 18.0; k += pi_4)
  {

  j = atan (k);
    
    if (j < HUGE)
    atan_sum += j;

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

  if (print_atan_sum != 0)
  printf ("The atan of %f = %f\n", k, atan (k));
  }
  
  if (print_atan_sum != 0)
  printf ("atan_sum == %.40e\n", atan_sum);

  if (fabs (fabs(atan_sum) - fabs(final_atan_sum)) < 1.0e-13)
  printf ("Atan Test Passed\n");
  else
  printf ("\n*****************ERROR IN ATAN TEST\n");
}
*/

double fabs ();

double atan (x)
double x;
{
double term;              
double term1;
double result;
double sum = 0.0;             
double sqrx = sqr(x);
double i_sqrx = (1.0 / sqrx);
double denominator = 3.0;
  if (x > HUGE) 
  {
  errno = EDOM;
  return (HUGE);
  } 

  if (x == 1.0)
  {
  return (pi_4);
  }
  else if (x == -1.0)
  {
  return (-pi_4);
  }

  else
  {
    if (x > 1.0)
    {
    result = (pi_2 - atan (1.0/x));
      if (result > HUGE) 
      {
      errno = ERANGE;
      return (HUGE);
      }
    return (result);
    }

    else if (sqrx < 1.0)
    {
    term = x;
    sum = x;
      do 
      {
      term = -term * sqrx;
      sum = sum + (term/denominator);
      denominator += 2.0;
      }
      while (fabs(term) >= _double_precision);
    result = sum;
      if (result > HUGE) 
      {
      errno = ERANGE;
      return (HUGE);
      }
    return (result);
    }

    else if (x < -1.0)
    {
    term = (1.0 / x);
    sum = ((-pi_2) - term);
    term = term * i_sqrx;
    term1 = term * (1.0 / denominator);
    sum += term1;
    denominator += 2.0; 
   
      do
      {
      term = -term * i_sqrx;
      term1 = term * (1.0 / denominator);
      sum += term1;
      denominator += 2.0; 
      }
      while (fabs(term) >= _double_precision);
    result = sum;
      if (result > HUGE) 
      {
      errno = ERANGE;
      return (HUGE);
      }
    return (result);  
    }
  }
}
