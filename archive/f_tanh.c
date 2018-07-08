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
*                  T A N H   F U N C T I O N                                  *
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
float tanh_sum = 0.0;
float final_tanh_sum = 1.399999e1;
float f_fabs ();
float f_tanh ();

#ifndef INTERNAL
float *f_ptr;
int i;
char *conv_ptr;
char print_tanh_sum = 1;
#endif

printf ("'f_tanh' Test\n");
  for (k = -f_two_pi; k < 18.0; k += f_pi_4)
  {
  printf (".");
  j = f_tanh (k);
  tanh_sum += j;

#ifdef DEBUG_MESSAGES
#ifndef INTERNAL
printf ("\nDifference is %.10e\n", (double) f_fabs (tanh_sum - final_tanh_sum));
  f_ptr = &j;
  conv_ptr = (char *) f_ptr;
    for (i = 0; i != 4; i++)
    printf ("conv_ptr -> %x\n", (*(conv_ptr + i) & 0x00ff));
#endif
#endif

#ifndef INTERNAL
  if (print_tanh_sum != 0)
  printf ("The tanh of %f = %f\n", (double) k, (double) j);
#endif
  }
  
#ifndef INTERNAL
  if (print_tanh_sum != 0)
  {
  printf ("tanh_sum == %.10e\n", (double) tanh_sum);
  printf ("final_tanh_sum == %.10e\n", (double) final_tanh_sum);
  }
#endif

printf ("sum = %f, final sum = %f\n", (double) tanh_sum, (double) final_tanh_sum);
  if (f_fabs (tanh_sum - final_tanh_sum) < (_float_precision * 1.0e3))
  printf ("Tanh Test Passed\n");
  else
  printf ("\n*****************ERROR IN TANH TEST\n");
}
*/


float f_sqrt ();
float f_sinh ();

float f_tanh (radians)
float radians;
{
#ifdef DEBUG_MESSAGES
float f1, f2, f3;
#endif

float sinhh;

sinhh = f_sinh (radians);

#ifdef DEBUG_MESSAGES
f1 = sqr(sinhh);
f2 = 1.0 + f1;
f3 = f_sqrt (f2);
printf ("sinhh = %f, f1 = %f, f2 = %f, f3 = %f\n", (double) sinhh, (double) f1, (double) f2, (double) f3);
#endif

return (sinhh / f_sqrt(1.0 + sqr(sinhh)));
}




