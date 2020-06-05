#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h> 
#include<string.h>
int main(int argc,char* argv[])
{
	//Defining the necessary structures
	
	struct dirent* current_directory;
	struct stat my_stat;
	struct tm lt;  
	struct passwd *pwd;
	char* dir_name = (char*)calloc(100,sizeof(char));
	if(argv[1] && argv[2])
	{
		strcpy(dir_name,argv[2]);
	}
	else if(!argv[2])
	{
		strcpy(dir_name,argv[1]);
	}
	//opening directory
	DIR *dr = opendir(dir_name);
	if (dr == NULL)
	{
		printf("Could not open directory \n");
		return 0;
	}
	else if(argc == 0)
	{
		dr = opendir(".");
		while ((current_directory = readdir(dr)) != NULL) 
            	{	printf("%s\n", current_directory->d_name);	}
            	return 0;
          } 	 					
	else if(argv[1][1] == 'l')
	{
		while( (current_directory = readdir(dr) ) )   
		  { 
			stat(current_directory->d_name, &my_stat);  
		        if ( (stat(current_directory->d_name, &my_stat) ) == 0 )
			{
        			pwd = getpwuid(my_stat.st_uid); // Get User-ID
    			} 
        	time_t t = my_stat.st_mtime;
        	localtime_r(&t, &lt);
        	char timebuf[80];
        	strftime(timebuf, sizeof(timebuf), "%c", &lt);
        	if (pwd != 0) 
		{
        		printf("%s \t %ld \t %s \t %s",pwd->pw_name, (long)my_stat.st_size, timebuf, current_directory->d_name);
        		printf("\n");
        	} 
		else
		{
		        printf("%d \t %ld \t %s \t %s",my_stat.st_uid, (long)my_stat.st_size, timebuf, current_directory->d_name);
            		printf("\n");
        	} 
	}
	return 0;
	}
	else if(argv[1][1] == 'a')
	{
		while((current_directory = readdir(dr)) !=NULL)
		{	
			{
				printf("%s \t",current_directory->d_name); 
			}
		}
	return 0;	
	}
	while((current_directory = readdir(dr)) !=NULL)
		{
			if(current_directory->d_name[0] !='.')
			{
			
		printf("%s \n",current_directory->d_name); 
			}	
		}
	closedir(dr);

	return 0;
}

