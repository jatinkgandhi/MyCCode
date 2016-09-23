/* Code to get the time stamp */
#include <stdio.h>
#include <time.h>
#include <string.h>

char *pDays[] = 
		{
			"Sunday",
			"Monday",
			"Tuesday",
			"Wednesday",
			"Thursday",
			"Friday",
			"Saturday"
		};
 
int main()
{
	time_t timer;
	struct tm *pstTime;



	
	time(&timer);
	pstTime = localtime(&timer);
	printf("ctime is %s\n", ctime(&timer));
	printf("%d:%d:%d",pstTime->tm_mday,pstTime->tm_mon, pstTime->tm_year);
	fprintf(stderr,"%02d/%02d/%s,%s,%d:%d\n",pstTime->tm_mday,pstTime->tm_mon, "2010",pDays[pstTime->tm_wday],pstTime->tm_hour,pstTime->tm_min);

	return 0;
}



