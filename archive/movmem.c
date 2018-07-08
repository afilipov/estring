
	.asm
	.linklist
	.symbols
	.endasm

#ifdef INTERNAL
#define movmem imovmem
#endif

char *movmem(dst,src,numb)
char *dst;
char *src;
int  numb;
{
char *tmp;

tmp = dst;
  while(numb)
  {
  *tmp++ = *src++;
  --numb;
  }
return(dst);
}

