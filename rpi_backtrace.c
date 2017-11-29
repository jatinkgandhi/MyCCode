
/* 
Code:
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/prctl.h>
#include <errno.h>
#include <execinfo.h>
#include <unistd.h>


#define MALLOC_TIMEOUT_MINUTES  (1)
#define SECONDS_IN_A_MINUTE             (60)

#define MALLOC_TIMEOUT  (MALLOC_TIMEOUT_MINUTES * SECONDS_IN_A_MINUTE)


static unsigned int t1,t2;


#define TOTAL_THREADS   (100)


pthread_t threads[TOTAL_THREADS];


#define BT_BUF_SIZE 100

void show_backtrace(void)
{
	int j, nptrs;
	void *buffer[BT_BUF_SIZE];
	char **strings;
	
	char thrname[16];

	nptrs = backtrace(buffer, BT_BUF_SIZE);
	
	strings = backtrace_symbols(buffer, nptrs);

	if (strings == NULL) {
		perror("backtrace_symbols");
		exit(EXIT_FAILURE);
	}

	printf("\n============================================\n");
	printf("                Thread backtrace              ");
	printf("\n============================================\n");

	pthread_getname_np(pthread_self(), thrname);

	if('\0' != thrname[0])
	{
		printf("I am : %s\n",thrname);
	}
	for (j = 0; j < nptrs; j++)
	{
		printf("%s\n", strings[j]);
	}

	printf("\n============================================\n");

	free(strings);
}

unsigned int getCurrentLocalTime(void)
{
	struct timespec t;

	if (clock_gettime(CLOCK_MONOTONIC, &t) == -1) {
		printf("The clock_gettime() function failed: %s\n", strerror(errno));
		return 0;
	}

	printf("seconds : %u, ns : %u\n",t.tv_sec, t.tv_nsec);
	return (t.tv_sec + (t.tv_nsec * 1.0e9));

}

void dummy3(void)
{
	show_backtrace();
}

void dummy2(void)
{
	dummy3();
}

void dummy1(void)
{
	dummy2();
}

void *ThreadFunc( void *ptr )
{
	char id[4];
	char name[20];
	char *pmem;
	pthread_t myid;

	sprintf(id,"%d",(int)ptr);

	memset(name,0,sizeof(name));

	strcpy(name, "Thread_");
	strcat(name, id);

	prctl( PR_SET_NAME, name);

	myid = pthread_self();


	pmem = malloc(1024 * 1024);
	if(NULL != pmem)
	{
		memset(pmem,id[0], 1);
	}
	
	while(1)
	{
		dummy1();
		sleep(1);
	}
}


main()
{

	int  iret, index;
	t1 = getCurrentLocalTime();
	printf("Current seconds : %u\n",t1);
	
	/* Create independent threads each of which will execute function */
	for(index = 0; index < TOTAL_THREADS; index++)
	{
		iret = pthread_create( &threads[index], NULL, ThreadFunc, (void*) index);
		if(iret)
		{
			fprintf(stderr,"Error - pthread_create() return code: %d\n",iret);
			exit(EXIT_FAILURE);
		}
	}

	for(index = 0; index < TOTAL_THREADS; index++)
	{
		pthread_join( threads[index], NULL);
	}

	exit(EXIT_SUCCESS);
}


#if 0
How to Compile:
gcc -lpthread -rdynamic -funwind-tables threads.c  -o testthr


The application must be compiled with -funwind-tables to make backtrace() work on ARM.
#endif
