
	.asm
	.linklist
	.symbols
	.endasm

#ifdef INTERNAL
#define fillmem ifillmem
#endif

void fillmem(dst,numb,byte)
char *dst;
int  numb;
char byte;
{
  while(numb)
  {
  *dst++ = byte;
  --numb;
  }
}


