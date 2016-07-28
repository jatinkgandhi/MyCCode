/* My C library function implementations 
Useful when we can't/should not use standard library functons for portablility or whatever purpose */

/* MY ATOI */
/* My own implementation of atoi  */

#define isAsciiDigit(n) ( ((n) >= '0') && ((n) <= '9'))
int local_atoi(char *numstring)
{
        int number,sign;

        number = 0;

        if(NULL == numstring) return number;

        if(*numstring == '-')
        {
            sign = -1;
            numstring++;
        }else if(*numstring == '+')
        {
           sign = 1;
           numstring++;
        }else
        {
           sign = 1;
        }

        while(*numstring != '\0')
        {
                if(isAsciiDigit(*numstring))
                {
                        number = (number * 10) + (*numstring - '0');
                }
                numstring++;
        }
        return (sign * number);

}


/*************************/

void local_strncat(char *dest, const char *src, size_t N)
{
        unsigned int i, j;

        if(NULL == dest || NULL == src) return;

        i = 0;
        while(dest[i] != '\0')
        {
            i++;
            if(i >= N)
            {
               break;
            }
        }

        j = 0;
        while(src[j] != '\0' && i < N)
        {
                dest[i++] = src[j++];
        }
}
