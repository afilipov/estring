#include "math.h"
#include "error.h"

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
*          S E R I E S  F O R  A R C T A N G E N T                           *
*                                                                            *
*        U S E S    F L O A T S    I N S T E A D    O F   D O U B L E S      *
*****************************************************************************/

extern const float f_pi, f_two_pi, f_pi_4;       /* pi */
extern const float f_pi_2;                       /* pi divided by 2 */
extern const float f_i_pi_2;                     /* inverse of pi_2 */

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
float atan_sum = 0.0;
float final_atan_sum = 2.07563762e1;
float f_atan ();

#ifndef INTERNAL
float f, *f_ptr;
int i;
char *conv_ptr;
char print_atan_sum = 1;
#endif

printf ("'f_atan' Test\n");
  for (k = -f_two_pi; k < 18.0; k += f_pi_4)
  {
  printf (".");
  j = f_atan (k);
    
    if (j < HUGE)
    atan_sum += j;

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
  if (print_atan_sum != 0)
  printf ("The atan of %f = %f\n", (double) k, (double) j);
#endif
  }
  
#ifndef INTERNAL
  if (print_atan_sum != 0)
  printf ("atan_sum == %.10e\n", (double) atan_sum);
#endif

  if (f_fabs (f_fabs (atan_sum) - f_fabs (final_atan_sum)) < (_float_precision * 1.0e3))
  printf ("Atan Test Passed\n");
  else
  printf ("\n*****************ERROR IN ATAN TEST\n");
}
*/


float f_atan (x)
float x;
{
float term;              
float term1;
float result;
float sum = 0.0;             
float sqrx = sqr(x);
float i_sqrx = (1.0 / sqrx);
float denominator = 3.0;

  if (x > HUGE) 
  {
  errno = EDOM;
  return (HUGE);
  } 

  if (x == 1.0)
  {
  return (f_pi_4);
  }
  else if (x == -1.0)
  {
  return (-f_pi_4);
  }
  else
  {
    if (x > 1.0)
    {
    result = (f_pi_2 - f_atan (1.0/x));
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
      while (f_fabs (term) >= _float_precision);
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
    sum = ((-f_pi_2) - term);
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
      while (f_fabs (term) >= _float_precision);
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

