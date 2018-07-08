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
*                          F L O O R                                          *
*                                                                            *
*        U S E S    F L O A T S    I N S T E A D    O F   D O U B L E S      *
******************************************************************************/


/*
#define DEBUG_MESSAGES  1
*/

extern const float f_pi, f_two_pi, f_pi_4;       /* pi */
extern const float f_pi_2;                       /* pi divided by 2 */
extern const float f_i_pi_2;                     /* inverse of pi_2 */

#ifdef INTERNAL
extern const float _float_precision;	 	/* result precision */
#else
extern float _float_precision;		 	/* result precision */
#endif

/*
main ()
{
float k, j;
float floor_sum = 0.0;
float final_floor_sum = 154.0;
float f_fabs ();
float f_floor ();

#ifndef INTERNAL
float *f_ptr;
int i;
char *conv_ptr;
char print_floor_sum = 1;
#endif

printf ("'f_floor' Test\n");
  for (k = -f_two_pi; k < 18.0; k += f_pi_4)
  {
  printf (".");
  j = f_floor (k);
  floor_sum += j;

#ifdef DEBUG_MESSAGES
#ifndef INTERNAL
  f_ptr = &j;
  conv_ptr = (char *) f_ptr;
    for (i = 0; i != 4; i++)
    printf ("conv_ptr -> %x\n", (*(conv_ptr + i) & 0x00ff));
#endif
#endif

#ifndef INTERNAL
    if (print_floor_sum != 0)
    {
    printf ("The floor of %f = %f\n", (double) k, (double) j);
    }
#endif
  }
  
#ifndef INTERNAL
  if (print_floor_sum != 0)
  printf ("floor_sum == %.10e\n", (double) floor_sum);
#endif

  if (f_fabs (floor_sum - final_floor_sum) < (_float_precision * 1.0e0))
  printf ("Floor Test Passed\n");
  else
  printf ("\n*****************ERROR IN FLOOR TEST\n");
}
*/


float f_floor (x)
float x;
{
float temp;
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
  temp = i_temp;
  return (temp);
  }

  else
  {
    if (i_temp > x)
    {
    i_temp -= 1;
    }
  temp = i_temp;
  return (temp);
  }
}
 
