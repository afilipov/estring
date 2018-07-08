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

/******************************************************************************
*   T A Y L O R  S E R I E S  A P P R O X A M A T I O N  F O R  S I N H       *
*                                                                             *
*         U S E S    F L O A T S    I N S T E A D    O F   D O U B L E S      *
******************************************************************************/

/*
#define DEBUG_MESSAGES  1
*/

extern const float f_pi, f_two_pi, f_pi_4;      /* pi */
extern const float f_pi_2;                      /* pi divided by 2 */
extern const float f_i_pi_2;                    /* inverse of pi_2 */

#ifdef INTERNAL
extern const float _float_precision;	 	/* result precision */
#else
extern float _float_precision;		 	/* result precision */
#endif

/*
main ()
{
float k, j;
float sinh_sum = 0.0;
float final_sinh_sum = 2.933488e7;
float f_fabs ();
float f_sinh ();

#ifndef INTERNAL
float *f_ptr;
int i;
char *conv_ptr;
char print_sinh_sum = 1;
#endif

printf ("'f_sinh' Test\n");
  for (k = -f_two_pi; k < 18.0; k += f_pi_4)
  {
  printf (".");
  j = f_sinh (k);
  sinh_sum += j;

#ifdef DEBUG_MESSAGES
#ifndef INTERNAL
printf ("\nDifference is %.10e\n", (double) f_fabs (sinh_sum - final_sinh_sum));
  f_ptr = &j;
  conv_ptr = (char *) f_ptr;
    for (i = 0; i != 4; i++)
    printf ("conv_ptr -> %x\n", (*(conv_ptr + i) & 0x00ff));
#endif
#endif

#ifndef INTERNAL
  if (print_sinh_sum != 0)
  printf ("The sinh of %f = %f\n", (double) k, (double) j);
#endif
  }
  
#ifndef INTERNAL
  if (print_sinh_sum != 0)
  {
  printf ("sinh_sum == %.10e\n", (double) sinh_sum);
  printf ("final_sinh_sum == %.10e\n", (double) final_sinh_sum);
  }
#endif

  if (f_fabs (sinh_sum - final_sinh_sum) < (_float_precision * 1.0e10))
  printf ("Sinh Test Passed\n");
  else
  printf ("\n*****************ERROR IN SINH TEST\n");
}
*/

float f_fabs ();

float f_sinh (radians)
float radians;
{
int k;
float term, sum;

  if (f_fabs (radians) > HUGE)
  {
  errno = ERANGE;
  return (HUGE);
  }

sum = radians;
term = radians;
k = 1;                  
  do
  {
  term  = (term * sqr(radians)) / (((float) 2.0 * k) * ((float) 2.0 *  k + (float) 1.0));
  sum = sum + term;
  k++;
  }
  while (f_fabs (term) >= _float_precision);

  if (f_fabs (sum) > HUGE)
  {
  errno = ERANGE;
  return (HUGE);
  }
return (sum);
}

