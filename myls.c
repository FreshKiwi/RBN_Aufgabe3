#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define DEBUG

int main(int argc, char *argv[])
{
    int aFlag= 0;
    int lFlag = 0;
    int pathIndex = 0;
    int opt;
    int i;

    DIR *dp;
    struct dirent *ep;
    struct stat fileInfo;


	while ((opt = getopt(argc, argv, "al")) != -1) {
               switch (opt) {
               case 'a':
                   aFlag = 1;
                   break;
               case 'l':
                   lFlag = 1;
                   break;
               }
           }
    pathIndex = optind;
	
    printf("Pfad: %s\n", argv[pathIndex]);
    if (pathIndex)
    {
		
		#ifdef DEBUG
        
        if (aFlag)
        {
            printf("mit -a\n");
        }
        if (lFlag)
        {
            printf("mit -l\n");
        }
        #endif
        
        
        dp = opendir(argv[pathIndex]);
        
        if (dp != NULL)
        {
            while (ep = readdir(dp))
            {
                lstat(ep->d_name, &fileInfo);
                
                if(lFlag){
					if(aFlag){
						printf("%lo\t ",(unsigned long)fileInfo.st_mode);
					}
					else{
						if(strncmp(ep->d_name,".", 1)==0)
							printf("%lo\t ",(unsigned long)fileInfo.st_mode);
					}    
				}
				
                if(aFlag)
                {
                    if(strncmp(ep->d_name,".", 1)==0)
						printf("%s\t\n",ep->d_name);
                }
                if(strncmp(ep->d_name,".", 1)!=0)
                {-a
					printf("%s\t\n",ep->d_name);
				}
                
                
			}
			(void)closedir(dp);
		}
        else
        {
            perror("Couldn't open the directory.");
        }
	}
    else 
    {
        dp = opendir("./");
       
        if (dp != NULL)
        {
            while (ep = readdir(dp))
            {
                lstat(ep->d_name, &fileInfo);
                
                if(lFlag){
					if(aFlag){
						printf("%lo\t ",(unsigned long)fileInfo.st_mode);
					}
					else{
						if(strncmp(ep->d_name,".", 1)==0)
							printf("%lo\t ",(unsigned long)fileInfo.st_mode);
					}    
				}
				
                if(aFlag)
                {
                    if(strncmp(ep->d_name,".", 1)==0)
						printf("%s\t\n",ep->d_name);
                }
                if(strncmp(ep->d_name,".", 1)!=0)
                {
					printf("%s\t\n",ep->d_name);
				}
                
                
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

