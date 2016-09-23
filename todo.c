/* 
 * GPL : Gandhi Public License ;-)
 * Nothin.., use the way you  like.., ;-)
 */


#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define	TIMESHEET	".csv"

#if 0
/* DOS style path */
#define	ROOTDIR		"C:\\Project\\TimeSheet\\"
#else
/* Cygwin path */
#define ROOTDIR		"/cygdrive/c/Project/TimeSheet/"
#endif

char *pchNewTask = "\n-------------------------------------------------------\nPlease Enter Task : ";

char pchTask[255];

FILE *pOut;
time_t timer;
struct tm *pstTime;

void init_system(void);
char getChoice(void);
void exit_system(void); 
int NewTask(void);
void CloseTask(void);
char getChoice(void);
void ShowTask(void);
void displayMenu(void);
int main()
{
	
	char ch;
	int execute = 1;

	init_system();

	while(execute)
	{
	switch(getChoice())
	{
		case 'n':
		case 'N':
		case '1':
		{
			if(NewTask())
			{
				execute = 0;
				break;
			}
		}break;


		case 's':
		case 'S':
		case '2':
		{
			ShowTask();
		}break;

		case 'e':
		case 'E':
		case '3':
		{
			execute = 0;
		}break;
		default:
		{
			printf("\nInvalid Choice\n");
		}break;
	}
	}

	exit_system();
	return 0;
}



char FileName[255];
char Number[17];

#define	SEPARATOR	"_-_"

void init_system(void)
{
		
	pOut = NULL;
	pstTime = NULL;

	memset(FileName,0,255);
	memset(Number,0,17);

	strcat(FileName,ROOTDIR);
	
	time(&timer);
	pstTime = localtime(&timer);

	//itoa(pstTime->tm_mday,Number,10);
	sprintf(Number, "%d", pstTime->tm_mday); 

	strcat(FileName,Number);
	strcat(FileName,SEPARATOR);

	memset(Number,0,17);
	//itoa(pstTime->tm_mon + 1,Number,10);
	sprintf(Number, "%d", pstTime->tm_mon + 1);

	strcat(FileName,Number);
	strcat(FileName,SEPARATOR);

	strcat(FileName,"2010.csv");

	

	pOut = fopen(FileName,"ab+");
	/* Go to last place */
	fseek(pOut,0,SEEK_END);

	if(NULL == pOut)
	{
		printf("Failed to create file : %s\n",FileName);
		while(1);
	}
	printf("\n(Enter \"exit\" to close)\n");

}

void exit_system(void)
{
	fclose(pOut);
	getchar();
}



int NewTask(void)
{
	int errcode;
	errcode = 0;
	while(1)	
	{
		memset(pchTask,0,255);
		printf("%s",pchNewTask);
		gets(pchTask);
		printf("\n-------------------------------------------------------\n");
		

		if(0 == strcmp(pchTask,"exit"))
		{

			errcode = 1;
			break;
		}

		if(NULL != pOut)
		{
			fprintf(pOut,"%s\n",pchTask);
		}else
		{
			printf("Please close file %s\n",TIMESHEET);
		}

	}
	return 	errcode;
}

void ShowTask(void)
{
	int i = 0;
	long size;
	long oldpos;


	oldpos = ftell (pOut);
	fseek(pOut,0,SEEK_END);
	size=ftell (pOut);
	if(size == 0)
	{
		printf("No Task Created\n");
		fseek(pOut,oldpos,SEEK_SET);
		return;
	}

	printf("Below are the tasks you planned for today\n");
	fseek(pOut,0,SEEK_SET);

	

	while(!feof(pOut))
	{
		i++;
		memset(pchTask,0,255);
		fgets(pchTask,255,pOut);
		printf("%d)    %s",i,pchTask);
	}
	return;
}



char getChoice(void)
{
	char choice;
	displayMenu();
	printf("%s","Please enter your choice\n");

	scanf("%c",&choice);
	while((getchar()) != '\n')
	;
	return choice;
}


void displayMenu(void)
{
	printf("\n------- Please Enter Your Choice-------\n");
	printf("1) New Task \n");
	printf("2) Show Task \n");
	printf("3) Exit \n");

}
