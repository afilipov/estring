
	.asm
	.linklist
	.symbols
	.endasm


#define LONG_MAX_POWER_OF_TEN		1000000000L

#ifdef INTERNAL
#define ltoa iltoa
#endif

char *ltoa (number, buffer, radix)
long number;
char *buffer;
int  radix;
{
char  c1, c2;
char  lead_zero;
char  *tbuffer;
unsigned long  base;

tbuffer = buffer;
  if (number == 0)
  {
  *tbuffer++ = '0';				/* zero is a special case */
  }
  else
  {
  lead_zero = 1;
    if (radix == 10)
    {
      if (number < 0)
      {
      *tbuffer++ = '-';				/* output sign */
      -number;
      }
    base = LONG_MAX_POWER_OF_TEN;		/* init number base */
      while (base != 0)
      {
      *tbuffer = (char) (number / base) + '0';	/* convert to ascii */
        if (lead_zero == 0 || *tbuffer != '0')
        {
        tbuffer++;
        lead_zero = 0;
        }
      number %= base;
      base /= 10;				/* decrease number base */
      }
    }
    else
    {
      if (radix == 16)
      {
        for (c1 = 28; c1 != -4; c1 -= 4)
        {
        c2 = ((char) (number >> c1) & 0x0f) + '0';
          if (lead_zero == 0 || c2 != '0')
          {
            if (c2 > '9')
            {
            c2 += 0x07;
            }
          *tbuffer++ = c2;
          lead_zero = 0;
          }
        }
      }
      else
      {
        if (radix == 2)
        {
          for (c1 = 31; c1 != -1; c1--)
          {
          c2 = ((char) (number >> c1) & 0x01) + '0';
            if (lead_zero == 0 || c2 != '0')
            {
            *tbuffer++ = c2;
            lead_zero = 0;
            }
          }
        }
        else
        {
          for (c1 = 30; c1 != -3; c1 -= 3)
          {
          c2 = ((char) (number >> c1) & 0x07) + '0';
            if (lead_zero == 0 || c2 != '0')
            {
            *tbuffer++ = c2;
            lead_zero = 0;
            }
          }
        }
      }
    }
  }
*tbuffer = 0;					/* terminate */
return (buffer);
}


