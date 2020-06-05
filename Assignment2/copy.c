#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
void main(int argc, char *argv[])
{
	// fs - source file
	int fs = open(argv[2],O_RDONLY);
	int size;
	char *buffer = (char*) calloc(1000, sizeof(char));
	char choice;
	if(argv[1][1]=='i')
{		
	printf("Do you want to continue ?(y/n) \n");
	scanf("%c",&choice);
	if(choice == 'y')
	{
	if(fs == -1)
		printf("File does not exists \n");
	else
	{
		size = read(fs,buffer,200);
	// fd - destination file
		buffer[size] = '\0';
		int fd = open(argv[3],O_RDWR);
		if(fd == -1)
		{	printf("Destination file does not exist! Creating new file \n");
			creat(argv[3],O_RDWR);
		}			
		write(fd,buffer,200);
		printf("File Copied \n");
	}}
	else
		printf("Progress Halted \n");
}
	else if(argv[1][1] == 'f')
	{
		if(fs == -1)
		printf("File does not exists \n");
	else
	{
		size = read(fs,buffer,200);
	// fd - destination file
		buffer[size] = '\0';
		int fd = open(argv[3],O_RDWR);
		if(fd == -1)
		{	printf("Destination file does not exist! Creating new file \n");
			creat(argv[3],O_RDWR);
		}			
		write(fd,buffer,200);
		printf("File Copied ! \n");
	}
	}
	else
		printf("Enter valid option \n");	
}		
		
