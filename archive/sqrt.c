
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
*              S Q U A R E R O O T  A P P R O X I M A T I O N                 * 
*                   B Y  N E W T O N ' S   M E T H O D                        *
*******************************************************************************

               Copyright (C) 1986 by 2500 A.D. Software, Inc.                 


   Sqrt takes a double precision argument and evaluates the square-root
   by Newton's Method. */

extern const double pi_4;

#ifdef INTERNAL
extern const double _double_precision;	 	/* result precision */
#define  table  itable
#else
extern double _double_precision;	 	/* result precision */
#endif

/*
main ()
{
double k, j;
double sqrt_sum = 0.0;
double final_sqrt_sum = 6.286802462757130172e1;
double fabs ();
double sqrt ();
double *f_ptr;
int i;
char   *conv_ptr;
char print_sqrt_sum = 0;

  for (k = 0.0; k < 18.0; k += pi_4)
  {

  j = sqrt (k);
    
    if (j < HUGE)
    sqrt_sum += j;

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

  if (print_sqrt_sum != 0)
  printf ("The sqrt of %f = %f\n", k, sqrt (k));
  }
  
  if (print_sqrt_sum != 0)
  printf ("sqrt_sum == %.40e\n", sqrt_sum);

  if (fabs (fabs(sqrt_sum) - fabs(final_sqrt_sum)) < 1.0e-13)
  printf ("Sqrt Test Passed\n");
  else
  printf ("\n*****************ERROR IN SQRT TEST\n");
}
*/

const double table[15] = {            9.9,             99.9,             999.9,
                                   9999.9,          99999.9,          999999.9,
                                9999999.9,       99999999.9,       999999999.9,
                             9999999999.9,    99999999999.9,    999999999999.9,
                          9999999999999.9, 99999999999999.9, 999999999999999.9};

double sqrt (x)
double x;            
{
double fabs ();
int i, count;
double result;
double prior_result;
double difference;

  if (x < 0.0)
  {
  errno = EDOM;
  return (0.0);
  }

  else if (x == 0.0)
  {
  return (0.0);
  }

  else if (x == 1.0)
  {
  return (1.0);
  }

  else 
  {

  /* get an initial guess  i.e. result == 2 * (sqrt (10)  raised to the n - 1
     power), where n is the number of decimal digits in the argument        */

    for (i = 0; i != 15; i++)
    {
      if (x < table[i])
      {
      break;
      }
    }
 
  result = 1.0;
 
    for (count = i; count > 0; count--)
    {
    result = result * 3.1622777;
    }

  result *= 2.0;   

    do
    {
    prior_result = result;                          
    result = result - (((result * result) - x) / (2.0 * result));  
    difference = (result - prior_result);       
    }     
    while (fabs (difference) >= _double_precision);
  }

  if (result > HUGE)
  {
  errno = ERANGE;
  return (HUGE);
  }
return (result);
}

