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
*                      L O G   B A S E  T E N                                 *
*                                                                             *
*         U S E S    F L O A T S    I N S T E A D    O F   D O U B L E S      *
*******************************************************************************

              log10 x = ln (x) / ln10                                        */ 


/*
#define DEBUG_MESSAGES  1
*/

extern const float f_pi, f_two_pi, f_pi_4;       /* pi */
extern const float f_pi_2;                       /* pi divided by 2 */
extern const float f_i_pi_2;                     /* inverse of pi_2 */
extern const float f_ln10;			 /* natural log of 10 */

#ifdef INTERNAL
extern const float _float_precision;	 	/* result precision */
#else
extern float _float_precision;		 	/* result precision */
#endif

/*
main ()
{
float k, j = 0;
float log_sum = 0.0;
float final_log_sum = 8.753295e1;
float f_fabs ();
float f_log10 ();

#ifndef INTERNAL
float *f_ptr;
int i;
char *conv_ptr;
char print_log_sum = 1;
#endif

printf ("'f_log10' Test\n");
  for (k = 0.0; k < 53.0; k = k + f_pi_4)
  {
  printf (".");
  j = f_log10 (k);
    if (k > 0.0)
    {
    log_sum = log_sum + j;
    }

#ifdef DEBUG_MESSAGES
#ifndef INTERNAL
  f_ptr = &j;
  conv_ptr = (char *) f_ptr;
    for (i = 0; i != 4; i++)
    printf ("conv_ptr -> %x\n", (*(conv_ptr + i) & 0x00ff));
#endif
#endif

#ifndef INTERNAL
    if (print_log_sum != 0)
    {
    printf ("The log10  of %f = %.10f\n", (double) k, (double) j);
    printf ("log_sum == %.10e\n\n", (double) log_sum);
    }
#endif
  }
  
#ifndef INTERNAL
  if (print_log_sum != 0)
  printf ("log_sum == %.10e\n", (double) log_sum);
#endif

  if (f_fabs (log_sum - final_log_sum) < (_float_precision * 1.0e3))
  printf ("Log10 Test Passed\n");
  else
  printf ("\n*****************ERROR IN LOG10 TEST\n");
}
*/


float f_ln ();

float f_log10 (x)
float x;
{
  if (x <= 0.0)
  {
  errno = EDOM;
  return (-HUGE);
  }

return (f_ln (x) / f_ln10);
}


