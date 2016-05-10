/*
 * Reading entire file and converting to list of lines.
 * Inspired from C# readAll().
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define null	NULL

#ifdef RELEASE_BUILD
#define LOGGER(X)
#else
#define LOGGER(X)	printf X
#endif

/*
 * function:    GetCount
 * description: This function will count number  of times specific character appears in
 *              the buffer.
 */
static int GetCount(const unsigned char *buffer,unsigned char character)
{
	int count;

	count = 0;

	while(*buffer != 0)
	{
		if(*buffer == character ) count++;
		buffer++;
	}
	return count;
}

/*
 * function:    ConvertToArray
 * description: Converts the buffer into multiple line array.
 */
static char ** ConvertToArray(char *buffer, int *total_no_of_lines)
{
	int total_lines;
	char **array;
	int index;
	int i;

	total_lines = 0;

	if(null == buffer)
	{
		LOGGER(("%s:%s:%d->Please enter valid input params\n",__FILE__,__func__,__LINE__));
		return null;
	}

	total_lines = GetCount(buffer,'\n');
	*total_no_of_lines = total_lines;

	if(0 == total_lines)
	{
		LOGGER(("%s:%s:%d->Zero lines found\n",__FILE__,__func__,__LINE__));
		return null;
	}

	array = (char **) malloc(total_lines * sizeof(char *));
	if(null == array)
	{
		LOGGER(("%s:%s:%d->Failed to allocate memory\n",__FILE__,__func__,__LINE__));
		return null;
	}

	/* Start pointing to beginning of strings.. */
	index = 0;
	array[index] = buffer;

	while(0 != *buffer)
	{
		if('\n' == *buffer)
		{
			/* Replacing \n with null terminater and assigning fixes FIXME and TODO */
			*buffer = 0;
			index++;
			buffer++;
			array[index] = buffer;

		}else
		{
			buffer++;
		}
	}

	return array;	
}
/* TODO: FIXME: THIS WILL NOT TERMINATE INDIVIDUAL LINES... 
  so strlen + 1, memset and then copy until cr+lf  are found */

static char ** ReadAll(const char *filename, int *total_bytes,  unsigned char **buffer, int *totallines)
{

	/* Basic version of code BEGIN */
	FILE *fileptr;
	long filesize;
	char **array;
 
	if(null == filename || null == total_bytes || null == buffer | null == totallines)
	{
		LOGGER(("%s:%s:%d->Please enter valid input params\n",__FILE__,__func__,__LINE__));

		return null;
	}
    fileptr = null;
	fileptr = fopen(filename, "rb");

	if(NULL == fileptr)
	{
		LOGGER(("Faile dot open file %s\n",filename));
		return null;
	}
	
	fseek(fileptr, 0, SEEK_END);

	filesize = ftell(fileptr);

	fseek(fileptr, 0, SEEK_SET);

	*buffer = (unsigned char *)malloc(filesize + 1);

	memset(*buffer,0,filesize + 1);

	fread(*buffer, filesize, 1, fileptr);

	fclose(fileptr);

	(*buffer)[filesize] = 0;

	/* Basic version of code ends. */

	/* Lets convert buffer to array */
	array = null;
	array = ConvertToArray(*buffer, totallines);

	return array;
}

/* Test Code */
int main(int argc, char **argv)
{

	int total_bytes = 0, total_no_lines,i;
	unsigned char *buffer = null;
	char **p;
	p = null;

	p = ReadAll("test.txt", &total_bytes, &buffer,&total_no_lines);

	if(null != p && total_no_lines > 0)
	{
		for(i = 0; i < total_no_lines; i++)
		{
			printf("%s\n",p[i]);
		}
	}

	if(NULL != buffer) free(buffer);

	return 0;
}
