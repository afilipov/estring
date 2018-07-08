
	.asm
	.linklist
	.symbols
	.endasm

#ifdef INTERNAL
#define atof iatof
#define __round __internal_round
#define __decimal_exponent __internal_decimal_exponent
#define __fraction_table __internal_fraction_table
#define __power_table __internal_power_table
#endif

#include "printf.h"

double atof (string)
char *string;
{
char negative = 0;
char neg_exponent = 0;
int fraction_digits = 0;
int exponent = 0;
double mantissa = 0.0;
double fraction = 0.0;

#ifndef INTERNAL
double *double_ptr;
#else
const double *double_ptr;
#endif

  while (*string == ' ' || *string == '\t')
  {
  string++;					/* skip lead spaces and tabs */
  }
  if (*string == '-')
  {
  negative = 1;					/* negative */
  string++;
  }
  else
  {
    if (*string == '+')
    {
    string++;
    }
  }
  while (*string >= '0' && *string <= '9')	/* get mantissa */
  {
  mantissa = (mantissa * 10.0) + (*string - '0');
  string++;
  }
  if (*string == '.')				/* decimal point ? */
  {
  string++;
    while (*string >= '0' && *string <= '9')	/* get fraction */
    {
    fraction = (fraction * 10.0) + (*string - '0');
    fraction_digits++;
    string++;
    }
  }
  if (*string == 'e' || *string == 'E')		/* exponent ? */
  {
  string++;
    if (*string == '-')				/* sign ? */
    {
    neg_exponent = 1;
    string++;
    }
    else
    {
      if (*string == '+')
      {
      string++;
      }
    }
    while (*string >= '0' && *string <= '9')	/* get exponent */
    {
    exponent = (exponent * 10) + (*string - '0');
    string++;
    }
  }
  if (fraction_digits != 0)			/* scale fraction */
  {
  double_ptr = __fraction_table;		/* get ptr to fraction table */
  fraction_digits &= 0x1ff;			/* mask count */
    while (fraction_digits != 0)
    {
      if ((fraction_digits & 1) != 0)		/* bit 0 == 1 */
      {
      fraction *= *double_ptr;
      }
    fraction_digits >>= 1;			/* get next bit 0 */
    double_ptr++;				/* next power of two */
    }
  }
mantissa += fraction;				/* add to mantissa */
  if (exponent != 0)				/* scale by exponent */
  {
    if (neg_exponent)
    {
    double_ptr = __fraction_table;		/* get ptr to fraction table */
    }
    else
    {
    double_ptr = __power_table;			/* get ptr to power table */
    }
  exponent &= 0x1ff;				/* mask exponent */
    while (exponent != 0)
    {
      if ((exponent & 1) != 0)			/* bit 0 == 1 */
      {
      mantissa *= *double_ptr;
      }
    exponent >>= 1;				/* get next bit 0 */
    double_ptr++;				/* next power of two */
    }
  }
  if (negative != 0)
  {
  -mantissa;					/* make negative */
  }
return (mantissa);
}

