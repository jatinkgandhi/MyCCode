#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

static int level = 0;
void printlogs(int level, char *format, ...)
{
        va_list args;

        va_start(args, format);
        while(level-- > 0)
                printf("____");
        vprintf(format, args);
        va_end(args);
}


void f4(void)
{
        level++;
        printlogs(level,"I am forth leve function %s(%d)\n",__func__,__LINE__);
        level--;
}

void f3(void)
{
        level++;
        printlogs(level,"I am third level function %s(%d)\n",__func__,__LINE__);
        f4();
        level--;
}
void f2(void)
{
        level++;
        printlogs(level, "I am second level function... %s(%d)\n",__func__,__LINE__);
        f3();
        printlogs(level, "Bye %s(%d)\n",__func__,__LINE__);
        level--;
}
void f1(void)
{
        level++;
        printlogs(level, "I am first level function %s(%d)\n",__func__,__LINE__);
        f2();
        printlogs(level,"Bye %s(%d)\n",__func__,__LINE__);
        level--;
}

int main(int argc, char **argv)
{

        level = 0;
        f1();
        printlogs(level,"%05d\n",10);
        return 0;
}
