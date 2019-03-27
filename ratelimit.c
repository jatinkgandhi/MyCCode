#include <stdio.h>
#include <time.h>
#include <sys/time.h>


#define WAIT_TIME	(5)

int getCurSec(void)
{
	struct timeval tv;
	if(0 == gettimeofday(&tv,NULL))
	{
		return tv.tv_sec;
	}

	return -1;
}

void ratefunc(void)
{
	static int prev = 0xBADC0DE;
	int curr;
	if(0xBADC0DE == prev) 
	{
		prev = getCurSec();
		return; // ignoring first call..,.
		
	}
	else
	{
		curr = getCurSec();
		if((curr - prev) < WAIT_TIME)
		{
			printf("Can not call this function this fast please wait %d seconds.,\n",WAIT_TIME);
			prev = curr;
			return;
		}else
		{
			prev = curr;
		}
	}

	printf("Function executed\n");
}


int main(int argc, char **argv)
{
	int i;

	for(i = 0; i < 6; i++)
	{
		ratefunc();
		sleep(i);
	}

	return 0;
}

