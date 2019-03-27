#include <pthread.h>
#include <stdio.h>

void *thread(void *p);
void *somethingcritical(void *);

int seconds = 1;

int main(int argc, char **argv)
{
	pthread_t tid,crit;


	if(0 != pthread_create(&tid,NULL,thread, NULL))
	{
		return -1;
	//	sleep(5);
	//	fclose(stdout);
	//	After 5 second logs will start comming in file
	//	freopen("/dev/null","w",stdout);
	}

	
	if(0 != pthread_create(&crit,NULL,somethingcritical, NULL))
	{
		return -1;
	}


	// sleep(5);
	// freopen("/dev/tty","w",stdout);
	pthread_join( tid, NULL);
	pthread_join( crit, NULL);

	return 0;
}
 
void *thread(void *p)
{

	while(1)
	{
		printf("some data\n");

		sleep(1);
	}
	return NULL;
}


void* somethingcritical(void *p)
{
	do
	{
		sleep(10);

		/* We are about to start someting critical, 
                * we don't want any log during this time */
		freopen("/dev/null","w",stdout);

		fprintf(stderr,"Someting critical\n");


		sleep(10);
		freopen("/dev/tty", "w", stdout);
	}while(0);
}
