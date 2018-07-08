
	.asm
	.linklist
	.symbols
	.endasm

#ifdef INTERNAL
#define atol iatol
#endif

long atol (string)
char *string;
{
int  negative = 0;
long number = 0;

  while (*string == ' ' || *string == '\t')	/* skip lead spaces and tabs */
  {
  string++;
  }
  if (*string == '-')
  {
  string++;					/* skip sign */
  negative = 1;
  }
  else 
  {
    if (*string == '+')
    {
    string++;
    }
  }
  while (*string >= '0' && *string <= '9')	/* now convert number */
  {
  number = (number * 10L) + (*string - '0');
  string++;
  }
  if (negative != 0)
  {
  -number;
  }
return (number);
}

