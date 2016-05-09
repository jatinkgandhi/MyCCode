/* JATIN GANDHI */
/* Print number to 7 Seg. format.
Just for fun...  */
#include <stdio.h>
#include <string.h>

struct _digit{
	char *firstline;
	char *secondline;
	char *thirdline;
};
/* Buffer that store the patterns.,*/
struct _digit digits[] = 
{	
	{" _ ",
	 "| |",
	 "|_|"}, 
	{"   ",
	 "  |",
	 "  |"}, 
	{" _ ",
	 " _|",
	 "|_ "},
	{" _ ",
	 " _|",
	 " _|"},
	 {"   ",
	 "|_|",
	 "  |"},
	 {" _ ",
	  "|_ ",
	  " _|"},
	{" _ ",
	 "|_ ",
	 "|_|"},
	 {"_ ",
	  " |",
	  " |"},
	 {" _ ",
	  "|_|",
	  "|_|"},
	 {" _ ",
	  "|_|",
	  " _|"}
};


char line[3][255];

void Print7Seg(int val)
{
	int multiplier,digit;
	int count;
	int tempval;
	int digitcount;

	tempval = val;

	/* Free up the memory  */
	memset(line[0],0,255);
	memset(line[1],0,255);
	memset(line[2],0,255);


	multiplier = 1;
	count = 0; 
	digitcount = 0;

	while(val >= multiplier )
	{
		multiplier *= 10;
		digitcount++;
	}

	digit = val;
	do
	{
		multiplier /= 10;

		if(multiplier != 0)
		{
			digit = val / multiplier;
		}

		/* Get reminder  */
		if(multiplier != 0)
			val %= multiplier;

		/* Due to division, it will give 10 for 10 as reminder
		 instead of 1.  */
		if(digit == 10)
		{
			digit = 1;
		}

		/* Store individual lines into print buffer. */
		strcat(line[0],digits[digit].firstline);
		strcat(line[1],digits[digit].secondline);
		strcat(line[2],digits[digit].thirdline);


		/* Reduce number of available digits.  */
		digitcount --;

	} 	while (digitcount > 0);

	printf("%s\n",line[0]);
	printf("%s\n",line[1]);
	printf("%s\n",line[2]);
}

/* Test Code */
main()
{
	int value;

	Print7Seg(1024*1024 * 5);

	sleep(5);


	while(1)
	{
		for(value = 0; value < 234; value++)
		{
			system("clear");
			Print7Seg(value);
			usleep(300000);

		}
	}

}
