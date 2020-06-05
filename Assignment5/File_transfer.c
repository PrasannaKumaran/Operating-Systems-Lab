#include <sys/ipc.h>
# define NULL 0
#include <sys/shm.h>
#include <sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/wait.h>
#include <stdio_ext.h>
#include<ctype.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>


int main()
{
char *a,*b,c;
int id,n,i;
int size;
int pid;
int fs;
char *fname;
printf("\n FILE TRANSER \n");
int pid_file;
int rd;
pid_file = shmget(111,50, IPC_CREAT| 00666 );
pid=fork();
if(pid>0)
{
	printf("Inside parent process \n");
	a = (char*)shmat(pid_file,NULL,0);
	printf("Enter the file name to be transferred \n");
	scanf(" %[^\n]",fname);
	fs = open(fname, O_RDONLY);
	if(fs == -1)
		printf("file does not exists \n");
	else
	{
		size = read(fs,a,500);
		a[size] = '\n';
	}
	wait(NULL);
	close(fs);
	shmdt(a);
}
else
{
	sleep(4);
	printf("Inside Child Process \n");
	
	b = (char*)shmat(pid_file,NULL,0);
	printf("Enter destination file name \n");
	scanf("%[^\n]",fname);
	int fd = open(fname,O_WRONLY |O_CREAT| O_TRUNC ,S_IRUSR|S_IRWXU| 00666);
	if(fd == -1)
	{
		printf("Destination doesnt exist \n");
		creat(fname,O_RDWR | 00666);
	}
	write(fd,b,200);
	printf("File copied \n");
	close(fd);
	shmdt(b);
}
shmctl(pid_file,IPC_RMID,NULL);
}

