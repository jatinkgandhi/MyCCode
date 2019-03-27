#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>




tree(char *path){

DIR *dirp;
struct dirent *dp;
static nivel = 0;
struct stat buf;
char fichero[256];
int i;

if((dirp = opendir(path)) == NULL){
    perror(path);
    return;
}

while((dp = readdir(dirp)) != NULL){
    snprintf(fichero, 255, "%s/%s", path, dp->d_name);
	printf("%s\n",fichero);
    if((buf.st_mode & S_IFMT) == S_IFDIR){
        for(i=0;i<nivel;i++)
            printf("\t");
        printf("%s\n", dp->d_name);
        ++nivel;
        tree(fichero);
        --nivel;
    }

}
}

main(int argc, char *argv[]){

int i;

if(argc < 2){
    printf("\nError. Use: %s directory\n", argv[0]);
    system("exit");
}
for(i=1;i<argc;i++)
    //if(argv[i][0] != '-')
        tree(argv[i]);
}
