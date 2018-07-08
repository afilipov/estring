#include "math.h"
#include "error.h"

#ifdef INTERNAL
#define printf internal_nf_printf
#endif

	.asm
	.linklist
	.symbols
	.endasm

/***************************************************************************
*                          F R E X P                                       *
**************************************************************************** 

          Copyright (C) 1986 by 2500 A.D. Software, Inc.
                                                  
   Function frexp takes a double operand, param1, and splits it into
   its mantissa, exponent and sign parts.  This function returns the
   mantissa as a double and leaves the exponent in the location pointed
   to by p. */


/*
#define DEBUG_MESSAGES  1
*/

extern const double pi, two_pi, pi_4;           /* pi */
extern const double pi_2;                       /* pi divided by 2 */
extern const double i_pi_2;                     /* inverse of pi_2 */


/*
main ()
{
double k, j;
double frexp_sum = 0.0;
double final_frexp_sum = 1.102924412804704346e1;
double fabs ();
double frexp ();
double *f_ptr;
int i, exp_sum = 0;
int final_exp_sum = 0x5a;
int *ptr, exponent;
char   *conv_ptr;
char print_frexp_sum = 1;

ptr = &exponent;
  for (k = -two_pi; k < 18.0; k += pi_4)
  {

  j = frexp (k, ptr);
  frexp_sum += j;
  exp_sum += *ptr;
  exp_sum &= 0xff;
#ifdef DEBUG_MESSAGES
  f_ptr = &j;
  conv_ptr = (char *) f_ptr;

    for (i = 0; i != 8; i++)
    printf ("conv_ptr -> %x\n", (*(conv_ptr + i) & 0x00ff));
#endif

    if (print_frexp_sum != 0)
    {
    printf ("The frexp of %f = %f\n", k, j);
    printf ("The exp of %f = %x\n\n", k, *ptr);
    }
  }
  
  if (print_frexp_sum != 0)
  {
  printf ("frexp_sum == %.40e\n", frexp_sum);
  printf ("exp_sum == %x\n", exp_sum);
  }

  if ((fabs (frexp_sum - final_frexp_sum) < 1.0e-5)
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


double frexp (param1, p)
double param1;
int *p;
{
unsigned char convert1[8];		/* must be pointer aligned */
unsigned char double_format[8];		/* must be pointer aligned */
double *conv_dbl_ptr;
double conv_dbl;
double *param1_ptr;
char *sign_ptr;
unsigned char *double_ptr;
unsigned char *conv_ptr1;
char sign_bit1; 
int exp1;
register int i;
int j;
char c1;

param1_ptr = &param1;
conv_ptr1 = ((unsigned char *) param1_ptr) + 7;
  for (i = 0; i != 8; i++)
  {
  convert1[i] = *conv_ptr1--;
  }

exp1 = (convert1[0] & 0x7f); 
exp1 &= 0x00ff;
exp1 <<= 4;
exp1 |= ((convert1[1] & 0xf0) >> 4);
*p = (exp1 - 0x3fe);                /* Mask-off the exponent and set exp_ptr */
sign_bit1 = convert1[0] & 0x80;
sign_ptr = &sign_bit1;              /* Mask-off the sign bit and set sign_ptr */

  if (sign_bit1 & 0x80)
  {
  double_format[0] = 0x00bf;
  }
  else
  {
  double_format[0] = 0x003f;
  }

double_format[1] = ((0xe << 4) | (convert1[1] & 0x0f));                  
double_format[2] = convert1[2];                        
double_format[3] = convert1[3];     /* Put the mantissa into this array */
double_format[4] = convert1[4];                       
double_format[5] = convert1[5];                   
double_format[6] = convert1[6];
double_format[7] = convert1[7];

j = 7;
  for (i = 0; i != 4; i++)
  {
  c1 = double_format[i];
  double_format[i] = double_format[j];
  double_format[j--] = c1;
  }

double_ptr = double_format;
conv_dbl_ptr = (double *) double_ptr;
conv_dbl = *conv_dbl_ptr;      /* conv_dbl = value pointed to by conv_dbl_ptr */
return (conv_dbl);                       /* return the mantissa */
}

