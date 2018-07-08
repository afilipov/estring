
	.asm
	.linklist
	.symbols
	.endasm

#ifdef  INTERNAL
#define  labs  ilabs
#endif

long labs (x)
long x;
{
if (x < 0)
return (-x);
else
return (x);
}


