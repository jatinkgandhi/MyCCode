
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

/* Maximum supported files in a directory */
#define MAX_FILES_IN_DIR        (15)
/* Supporting 8.3 only */
#define MAX_FILE_NAME_LEN        (12)


/* LOGIC:
 * Read directory entry.
 * if it is "." or ".." continue getting next.
 * if it is hidden file (starts with ".") continue getting next.
 * allocate buffer to store file name in the list.
 * copy the file name.
 * increase total count.
 * */
char **getlistoffiles(char *directory, int *totalfiles)
{
    char **list;
    int total_files;
        DIR *d;
    struct dirent *dir;

    if(NULL == directory || NULL == totalfiles) return NULL;

         d = opendir(directory);


    list = (char **)malloc(MAX_FILES_IN_DIR * sizeof(char *));
    if(NULL == list)
    {
        return NULL;
    }

    total_files = 0;
    *totalfiles = 0;
    while((dir = readdir(d)) != NULL)
    {
        if((0 == strcmp(dir->d_name,".")) || (0 == strcmp(dir->d_name,"..")))
        {
            continue;
        }
        /* Allocate memory first for each name */
        list[total_files] = (char *)malloc(MAX_FILE_NAME_LEN * sizeof(char));
        if(NULL == list[total_files])
        {
            break;
        }
        strncpy(list[total_files], dir->d_name, MAX_FILE_NAME_LEN - 1);
        total_files ++;
        if(total_files >= MAX_FILES_IN_DIR)
        {
            break;
        }
    }

    *totalfiles = total_files;
    return list;

}

void freelistoffiles(char **list, int totalfiles)
{
    int index;
    
    if(NULL == list || NULL == *list || 0 == totalfiles )
    {
        return;
    }

    for(index = 0; index < totalfiles; index++)
    {
            if(NULL != list[index])
            {
                free(list[index]);
                list[index] = NULL;
            }
    }
    /* No dangling pointers snake is destroyed., 
      * destroy the head too.., */
    *list = NULL;
}

/* Test code */
int main(int argc, char **argv)
{

    char **list;
    int totalfiles =  0;
    int index;

    list = getlistoffiles(".", &totalfiles);

    printf("total files: %d\n",totalfiles);

    for(index = 0; index < totalfiles; index++)
    {
        if(NULL == list) break;
        if(NULL == list[index]) break;

        printf("File Name: %d is %s\n",index, list[index]);
    }
 
    
    freelistoffiles(list, totalfiles);

    return 0;
}
