/* Conditional debug string -> Release build no logs., debug build, logs.*/
#include <stdio.h>

#ifdef DEBUGBUILD
#define LOG(string_format, ...) do {\
     printf("%s()->%d: ", __func__, __LINE__);     \
     printf(string_format, ##__VA_ARGS__);          \
} while (0)
#else
#define LOG(fmt, ...)
#endif


int main(int argc, char **argv)
{
     LOG("This is the information : %s\n","Some info\n");
     LOG("This is another data : %f\n",23.92);
     LOG("Bought %d kg tomato\n",3);
     printf("Done\n");
     return 0;
}

