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

/***************************************************************************
*                          F R E X P                                       *
*                                                                            *
*        U S E S    F L O A T S    I N S T E A D    O F   D O U B L E S      *
**************************************************************************** 

          Copyright (C) 1986 by 2500 A.D. Software, Inc.
                                                  
   Function frexp takes a float operand, param1, and splits it into
   its mantissa, exponent and sign parts.  This function returns the
   mantissa as a float and leaves the exponent in the location pointed
   to by p. */


/*
#define DEBUG_MESSAGES  1
*/

extern const float f_pi, f_two_pi, f_pi_4;       /* pi */
extern const float f_pi_2;                       /* pi divided by 2 */
extern const float f_i_pi_2;                     /* inverse of pi_2 */
extern const float _float_precision;		 /* result precision */


/*
main ()
{
float k, j;
float frexp_sum = 0.0;
float final_frexp_sum = 9.935486e0;
float f_fabs ();
float f_frexp ();
int i, exp_sum = 0;
int final_exp_sum = 0x45;
int *ptr, exponent;

#ifndef INTERNAL
char   *conv_ptr;
float *f_ptr;
char print_frexp_sum = 1;
#endif

printf ("'f_frexp' Test\n");
ptr = &exponent;
  for (k = -f_two_pi; k < 18.0; k += f_pi_4)
  {
  printf (".");
  j = f_frexp (k, ptr);
  frexp_sum += j;
  exp_sum += *ptr;
  exp_sum &= 0xff;

#ifdef DEBUG_MESSAGES
#ifndef INTERNAL
  f_ptr = &j;
  conv_ptr = (char *) f_ptr;
    for (i = 0; i != 4; i++)
    printf ("conv_ptr -> %x\n", (*(conv_ptr + i) & 0x00ff));
#endif
#endif

#ifndef INTERNAL
    if (print_frexp_sum != 0)
    {
    printf ("The frexp of %f = %f\n", (double) k, (double) j);
    printf ("The exp of %f = %x\n\n", (double) k, *ptr);
    }
#endif
  }
  
#ifndef INTERNAL
  if (print_frexp_sum != 0)
  {
  printf ("frexp_sum == %.8e\n", (double) frexp_sum);
  printf ("exp_sum == %x\n", exp_sum);
  }
#endif

  if ((f_fabs (frexp_sum - final_frexp_sum) < (_float_precision * 1.0e3))
      && ((exp_sum - final_exp_sum) == 0))
  {
  printf ("Frexp Test Passed\n");
  }
  else
  {
  printf ("\n*****************ERROR IN FREXP TEST\n");
  }
}
*/


float f_frexp (param1, p)
float param1;
int *p;
{
unsigned char convert1[4];		/* must be pointer aligned */
unsigned char float_format[4];		/* must be pointer aligned */
float *conv_flt_ptr;
float conv_flt;
float *param1_ptr;
char *sign_ptr;
unsigned char *float_ptr;
unsigned char *conv_ptr1;
char sign_bit1; 
int exp1;
register int i;
int j;
char c1;

param1_ptr = &param1;
conv_ptr1 = ((unsigned char *) param1_ptr) + 3;
  for (i = 0; i != 4; i++)
  {
  convert1[i] = *conv_ptr1--;
  }

exp1 = (convert1[0] & 0x7f); 
exp1 &= 0x00ff;
exp1 <<= 1;
exp1 |= ((convert1[1] & 0x80) >> 7);
                                    /*exp_ptr = &exp1;*/
*p = (exp1 - 0x7e);                /* Mask-off the exponent and set exp_ptr */
sign_bit1 = convert1[0] & 0x80;
sign_ptr = &sign_bit1;              /* Mask-off the sign bit and set sign_ptr */

  if (sign_bit1 & 0x80)
  {
  float_format[0] = 0x00bf;
  }
  else
  {
  float_format[0] = 0x003f;
  }

float_format[1] = (convert1[1] & 0x7f);                  
float_format[2] = convert1[2];                        
float_format[3] = convert1[3];     /* Put the mantissa into this array */

j = 3;
  for (i = 0; i != 2; i++)
  {
  c1 = float_format[i];
  float_format[i] = float_format[j];
  float_format[j--] = c1;
  }

float_ptr = float_format;
conv_flt_ptr = (float *) float_ptr;
conv_flt = *conv_flt_ptr;      /* conv_flt = value pointed to by conv_flt_ptr */
return (conv_flt);                       /* return the mantissa */
}

