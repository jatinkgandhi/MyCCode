/* Converts 100x 100 image to binary Bug: flipped binary */
#include <stdio.h>

FILE *p;
#define	WIDTH	100
#define	HEIGHT	100

#define	THRESHOLD	100

int main(int argc, char **argv)
{
	unsigned char y,r,g,b;
	int width,height;

	p = NULL;

	p = fopen("in.bmp","rb+");

	if(NULL == p) return -1;

	fseek(p,SEEK_SET,54);

	width = 1;
	height = 1;

	while(!feof(p))
	{
		fscanf(p,"%c",&b);
		fscanf(p,"%c",&g);
		fscanf(p,"%c",&r);

		y = (unsigned char) ((0.11 * b) + (0.59 * g) + (0.30 * r));
		

		printf("%c",y > THRESHOLD ? '1' : '0');

		width++;
		if(width >= WIDTH)
		{
			height++;
			printf("\n");
			width = 0;
		}
		if(height >= HEIGHT)	break;

	}	
	fclose(p);
	return 0;
}
