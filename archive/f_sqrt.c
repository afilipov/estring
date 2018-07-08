#include "math.h"
#include "error.h"
#include "stdlib.h"

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

/******************************************************************************
*              S Q U A R E R O O T  A P P R O X I M A T I O N                 * 
*                   B Y  N E W T O N ' S   M E T H O D                        *
*                                                                             *
*         U S E S    F L O A T S    I N S T E A D    O F   D O U B L E S      *
*******************************************************************************

               Copyright (C) 1986 by 2500 A.D. Software, Inc.                 


   Sqrt takes a single precision argument and evaluates the square-root
   by Newton's Method. */

extern const float f_pi_4;

#ifdef INTERNAL
extern const float _float_precision;	 	/* result precision */
#define  f_table  if_table
#else
extern float _float_precision;		 	/* result precision */
#endif

float f_fabs ();

/*
main ()
{
float k, j;
float sqrt_sum = 0.0;
float final_sqrt_sum = 6.286802e1;
float f_sqrt ();

#ifndef INTERNAL
float *f_ptr;
int i;
char *conv_ptr;
char print_sqrt_sum = 1;
#endif

printf ("'f_sqrt' Test\n");
  for (k = 0.0; k < 18.0; k += f_pi_4)
  {
  printf (".");
  j = f_sqrt (k);
    if (j < HUGE)
    sqrt_sum += j;

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
  if (print_sqrt_sum != 0)
  printf ("The sqrt of %f = %f\n", (double) k, (double) j);
#endif
  }
  
#ifndef INTERNAL
  if (print_sqrt_sum != 0)
  printf ("sqrt_sum == %.10e\n", (double) sqrt_sum);
#endif

  if (f_fabs (f_fabs (sqrt_sum) - f_fabs (final_sqrt_sum)) < (_float_precision * 1.0e3))
  printf ("Sqrt Test Passed\n");
  else
  printf ("\n*****************ERROR IN SQRT TEST\n");
}
*/

const float f_table[8] = {    9.9,     99.9,     999.9,     9999.9,
                          99999.9, 999999.9, 9999999.9, 99999999.9};

float f_sqrt (x)
float x;            
{
int i, count;
float result;
float prior_result;
float difference;

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

    for (i = 0; i != 8; i++)
    {
      if (x < f_table[i])
      {
      break;
      }
    }
 
  result = 1.0;
 
    for (count = i; count > 0; count--)
    {
    result = result * 3.1622777;
    }

  result *= (float) 2.0;   

    do
    {
    prior_result = result;                          
    result = result - (((result * result) - x) / (2.0 * result));  
    difference = (result - prior_result);       
    }     
    while (f_fabs (difference) >= _float_precision);
  }

  if (result > HUGE)
  {
  errno = ERANGE;
  return (HUGE);
  }
return (result);
}

