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
*                          F L O O R                                          *
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
double floor_sum = 0.0;
double final_floor_sum = 1.55e2;
double fabs ();
double floor ();
double *f_ptr;
int i;
char *conv_ptr;
char print_floor_sum = 1;

  for (k = -two_pi; k < 18.0; k += pi_4)
  {

  j = floor (k);
  floor_sum += j;
#ifdef DEBUG_MESSAGES
  f_ptr = &j;
  conv_ptr = (char *) f_ptr;

    for (i = 0; i != 8; i++)
    printf ("conv_ptr -> %x\n", (*(conv_ptr + i) & 0x00ff));
#endif

    if (print_floor_sum != 0)
    {
    printf ("The floor of %f = %f\n", k, floor (k));
    }
  }
  
  if (print_floor_sum != 0)
  printf ("floor_sum == %.40e\n", floor_sum);

  if (fabs (floor_sum - final_floor_sum) < 1.0e-5)
  printf ("Floor Test Passed\n");
  else
  printf ("\n*****************ERROR IN FLOOR TEST\n");
}
*/


double floor (x)
double x;
{
double temp;
int i_temp;
  
i_temp = (int)x;

  if ((x - i_temp) == 0.0)
  {
  return (x);
  }

  else if (x == 0.0)
  {
  return (0.0);
  }

  else if (x < 0.0) 
  {
    if (i_temp > x)
    {
    i_temp -= 1;
    }
  temp = (double)i_temp;
  return (temp);
  }

  else
  {
    if (i_temp > x)
    {
    i_temp -= 1;
    }
  temp = (double)i_temp;
  return (temp);
  }
}
 
