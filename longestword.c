
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH		(255)

int SP_GetLongestWord(char *line, int length, char **longestword);

ssize_t getline(char **lineptr, size_t *n, FILE *stream) {
    int c;
    size_t i = 0;

    if (*lineptr == NULL) {
        *n = 128;
        *lineptr = malloc(*n);
    }

    while ((c = fgetc(stream)) != EOF) {
        if (i + 1 >= *n) {
            *n *= 2;
            *lineptr = realloc(*lineptr, *n);
        }
        (*lineptr)[i++] = c;
        if (c == '\n') break;
    }

    (*lineptr)[i] = '\0';
    return i ? i : -1;
}

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
	    pchLongestWord[i32LongestWordLen+1] = '\0';
		printf("Longest word is : %s\nLength: %d\n", pchLongestWord, i32LongestWordLen );
	}
	
}

int SP_GetLongestWord(char *line, int length, char **longestword)
{
	int maxlength;
	int current_len;
    int current_word_len;
	
	if(NULL == line || 0 == length || NULL == longestword)
	{
		return -1;
	}

	maxlength = current_len = 0;
    current_word_len = 0;
	*longestword = line;

	do
	{
        #ifdef DEBUG
        printf("%c", *line);
        current_word_len++;
        #endif
        // Without \n or \0, it will skip the last word. So we need to check for \n and \0 as well.
		if(' ' == *line || '\t' == *line || '\n' == *line || '\0' == *line)
		{
			if(current_len > maxlength)
			{
				*longestword = line - current_len;
				maxlength = current_len;
			}
			current_len = 0;
            #ifdef DEBUG
            printf(" : %d\n", current_word_len - 1);
            current_word_len = 0;
            #endif
		}
		
		current_len ++;
		line ++;
	}while(NULL != line && '\0' != *line);
	/* Boundry case single word is passed. */
	if(0 == maxlength && current_len > 0)
	{
	    *longestword = line - current_len;
	    maxlength = current_len-1; // we run till string terminator '\0';
	}
	return maxlength - 1; // exclude the space/tab/newline character/'\0';
}
