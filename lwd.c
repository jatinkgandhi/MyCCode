 /* File for Last W. Day :-) */


#include <stdio.h>
#include <string.h>

static unsigned char data[255];

int main(int argc, char **argv)
{
        FILE *pfile;
        int flush;

        pfile = fopen("test.bin","wb+");
        if(NULL == pfile)
        {
                printf("Failed to open the file\n");
                return 0;
        }

        memset(data,0xFF, sizeof(data));

        printf("data : %02x, %02x\n", data[0], data[1]);



        flush = 0;
        while(1)
        {
                fwrite(data, 1, 255, pfile);
                flush++;
                if(flush > 100)
                {
                        fflush(pfile);
                        flush = 0;
                }
        }

        fclose(pfile);
        return 0;
}
