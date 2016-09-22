#include <stdio.h>

#define BUFF_SIZE       (255)
char buff[BUFF_SIZE];

int main(int argc, char **argv)
{
        int separator;
        FILE *pfinputfile;
        char *current;
        if(argc < 3)
        {
                        printf("Usage: .\\split <file name> <character>\n");
                        return -1;
        }

        pfinputfile = fopen(argv[1],"rb");
        if(NULL ==  pfinputfile)
        {
                printf("Failed to open the file\n");
                return -1;
        }


        /* Looks good to go..,*/
        separator = argv[2][0]; /* First character as a separator */
        while(!feof(pfinputfile))
        {
                memset(buff,0,sizeof(buff));

                fgets(buff,sizeof(buff),pfinputfile);
                current = &(buff[0]);

                if(NULL == strchr(buff,separator))
                {
                        continue;
                }

                while((NULL != current) &&  ('\0' != *current ))
                {
                        if(*current == separator)
                        {
                                printf("$");
                        }else
                        {
                                printf("%c",*current);
                        }
                        current++;
                }

        }
        if(NULL !=  pfinputfile)
        {
                fclose(pfinputfile);
        }
        return 0;
}
