#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define NDEBUG

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
    struct passwd *pw;
    struct group *gp;
    char date[256];


    while ((opt = getopt(argc, argv, "al")) != -1)
    {
        switch (opt)
        {
        case 'a':
            aFlag = 1;
            break;
        case 'l':
            lFlag = 1;
            break;
        }
    }

    if (optind < argc)
        pathIndex = optind;

    if (pathIndex)
        dp = opendir(argv[pathIndex]);
    else
        dp = opendir("./");

#ifdef DEBUG
    printf("Pfad: %s\n", argv[pathIndex]);
    if (aFlag)
        printf("mit -a\n");
    if (lFlag)
        printf("mit -l\n");
#endif


    if (dp != NULL)
    {

        while (ep = readdir(dp))
        {
            lstat(ep->d_name, &fileInfo);
            pw = getpwuid(fileInfo.st_uid);
            gp = getgrgid(fileInfo.st_gid);

            if(lFlag)
            {
                if(aFlag)
                {
                    printf( (S_ISDIR(fileInfo.st_mode)) ? "d" : "-");
                    printf( (fileInfo.st_mode & S_IRUSR) ? "r" : "-");
                    printf( (fileInfo.st_mode & S_IWUSR) ? "w" : "-");
                    printf( (fileInfo.st_mode & S_IXUSR) ? "x" : "-");
                    printf( (fileInfo.st_mode & S_IRGRP) ? "r" : "-");
                    printf( (fileInfo.st_mode & S_IWGRP) ? "w" : "-");
                    printf( (fileInfo.st_mode & S_IXGRP) ? "x" : "-");
                    printf( (fileInfo.st_mode & S_IROTH) ? "r" : "-");
                    printf( (fileInfo.st_mode & S_IWOTH) ? "w" : "-");
                    printf( (fileInfo.st_mode & S_IXOTH) ? "x\t" : "-\t");
                    printf( "%lu\t",fileInfo.st_nlink);
                    printf( "%s\t", pw->pw_name );
                    printf( "%s\t", gp->gr_name );
                    printf( "%lu\t",fileInfo.st_size);

                    strcpy(date,ctime(&fileInfo.st_mtime));
                    date[strlen(date)-1] = '\0';
                    printf( "%s\t", date);

                }
                else
                {
                    if(strncmp(ep->d_name,".", 1)!=0)
                    {
                        printf( (S_ISDIR(fileInfo.st_mode)) ? "d" : "-");
                        printf( (fileInfo.st_mode & S_IRUSR) ? "r" : "-");
                        printf( (fileInfo.st_mode & S_IWUSR) ? "w" : "-");
                        printf( (fileInfo.st_mode & S_IXUSR) ? "x" : "-");
                        printf( (fileInfo.st_mode & S_IRGRP) ? "r" : "-");
                        printf( (fileInfo.st_mode & S_IWGRP) ? "w" : "-");
                        printf( (fileInfo.st_mode & S_IXGRP) ? "x" : "-");
                        printf( (fileInfo.st_mode & S_IROTH) ? "r" : "-");
                        printf( (fileInfo.st_mode & S_IWOTH) ? "w" : "-");
                        printf( (fileInfo.st_mode & S_IXOTH) ? "x\t" : "-\t");
                        printf( "%lu\t",fileInfo.st_nlink);
                        printf( "%s\t", pw->pw_name );
                        printf( "%s\t", gp->gr_name );
                        printf( "%lu\t",fileInfo.st_size);

                        strcpy(date,ctime(&fileInfo.st_mtime));
                        date[strlen(date)-1] = '\0';
                        printf( "%s\t", date);

                    }
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
    {
        perror("Couldn't open the directory.");
    }
}

