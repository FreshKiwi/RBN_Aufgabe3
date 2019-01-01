#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>


int main(int argc, char *argv[])
{
    int aFlag= 0;
    int lFlag = 0;
    int alFlag = 0;
    int pathIndex = 0;
    int i;

    DIR *dp;
    struct dirent *ep;
    struct stat fileInfo;

    // durch getopt() ersetzen
    for(i=1; i< argc; i++){
        if(strcmp("-a",argv[i]) == 0) aFlag=1;
        else if(strcmp("-l",argv[i]) == 0) lFlag=1;
        else if(strcmp("-al",argv[i]) == 0) alFlag=1;
        else pathIndex = i;
    }

    if((aFlag|| lFlag )&& alFlag) perror("too many arguments!");
    
    if (pathIndex)
    {
        printf("Pfad: %s\n", argv[pathIndex]);
        if (aFlag)
        {
            printf("mit -a\n");
        }
        if (lFlag)
        {
            printf("mit -l\n");
        }
        if (alFlag)
        {
            printf("mit -al\n");
        }
        dp = opendir(argv[pathIndex]);
        // hier mit lstat() Informatioen ausgehend von Optionsparametern ausgeben
        if (dp != NULL)
        {
            while (ep = readdir(dp))
                //lstat(ep->d_name, &fileInfo);
                if(aFlag){
                    printf("%d  %s\n",fileInfo.st_mode, ep->d_name);    
                }
                else{
                    if(strncmp(ep->d_name,".", 1)!=0)
                    printf("%d  %s\n",fileInfo.st_mode, ep->d_name);
                }
                
                (void)closedir(dp);
        }
        else
            perror("Couldn't open the directory.");
    }
    else {
        dp = opendir("./");
        if (dp != NULL)
        {
            while (ep = readdir(dp))
                if(aFlag){
                    printf("%d  %s\n",fileInfo.st_mode, ep->d_name);    
                }
                else{
                    if(strncmp(ep->d_name,".", 1)!=0)
                    printf("%d  %s\n",fileInfo.st_mode, ep->d_name);
                }
                
                (void)closedir(dp);
        }
        else
            perror("Couldn't open the directory");
    }
    
    if (argc > 5)
    {
        printf("Too many arguments supplied.\n");
    }
}
