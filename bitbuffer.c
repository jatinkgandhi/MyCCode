#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char buff[10];

void setBitInBuffer(char *buffer, size_t size, int bit)
{
	int index;
	int bitpos;
	
	
	if(NULL == buffer || 0 == size) return;
	
	if(bit >= (size * 8))	return;
	
	index = bit / 8;
	bitpos = bit - (index * 8);

	
	// printf("index = %d, bitpos = %d\n",index,bitpos);
	buffer[index] = buffer[index] | (1 << bitpos);
	
	return;
}


void resetBitInBuffer(char *buffer, size_t size, int bit)
{
	int index;
	int bitpos;
	
	
	if(NULL == buffer || 0 == size) return;
	
	if(bit >= (size * 8))	return;
	
	index = bit / 8;
	bitpos = bit - (index * 8);
	
	buffer[index] = buffer[index] & (~(1 << bitpos));
	
	return;
}

int getBitInBuffer(char *buffer, size_t size, int bit)
{
	int index;
	int bitpos;
	
	
	if(NULL == buffer || 0 == size) return;
	
	if(bit >= (size * 8))	return;
	
	index = bit / 8;
	bitpos = bit - (index * 8);
	
	// printf("index = %d, bitpos = %d\n",index,bitpos);
	return (((buffer[index] & (1 << bitpos)) >> bitpos) == 1);
}



/* Test code */

#define SETNCHECK(n)\
{\
	setBitInBuffer(buff,sizeof(buff),n);\
	printf("Bit %d is : %d\n",n, getBitInBuffer(buff,sizeof(buff),n));\
}

#define RESETNCHECK(n)\
{\
	resetBitInBuffer(buff,sizeof(buff),n);\
	printf("Bit %d is : %d\n",n, getBitInBuffer(buff,sizeof(buff),n));\
}

int main(int argc, char **argv)
{
	int bit;
	memset (buff,0,sizeof(buff));
	
	for(bit = 0; bit < (sizeof(buff) * 8); bit+= 2)
	{
		SETNCHECK(bit);
	}

	SETNCHECK(1);
	RESETNCHECK(1);

	for(bit = 0; bit < (sizeof(buff) * 8); bit+= 2)
	{
		RESETNCHECK(bit);
	}
	return 0;
}
