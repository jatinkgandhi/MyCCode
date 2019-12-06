#include <stdio.h>
#include <stdlib.h>

#define LINE_LENGTH		(255)

int SP_GetLongestWord(char *line, int length, char **longestword);

int main(int argc, char **argv)
{
	char *pchLongestWord;
	int   i32LongestWordLen;
	char  *pchLine;
	size_t  i32actualLength;
	pchLine = malloc(LINE_LENGTH * sizeof(char));
	
	if(NULL == pchLine)
	{
		return -1;
	}
	
	memset(pchLine,0,LINE_LENGTH);
	printf("Enter the line: ");
	getline(&pchLine, &i32actualLength, stdin);
    printf("\nLine: %s\n",pchLine);
	i32LongestWordLen = SP_GetLongestWord(pchLine, i32actualLength, &pchLongestWord);
	
	if(i32LongestWordLen > 0)
	{
	    pchLongestWord[i32LongestWordLen--] = '\0';
		printf("Longest word is : %s, Length: %d\n", pchLongestWord, i32LongestWordLen );
	}
	
}

int SP_GetLongestWord(char *line, int length, char **longestword)
{
	int maxlength;
	int current_len;
	
	if(NULL == line || 0 == length || NULL == longestword)
	{
		return -1;
	}

	maxlength = current_len = 0;
	*longestword = line;

	while(NULL != line && '\0' != *line)
	{
		if(' ' == *line || '\t' == *line)
		{
			if(current_len > maxlength)
			{
				*longestword = line - current_len;
				maxlength = current_len;
			}
			current_len = 0;
		}
		
		current_len ++;
		line ++;
	}
	
	return maxlength;
}
