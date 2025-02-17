#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct processes
{
	int arrival_time;
	int burst_time;
	char process_id;
	int turnaround_time;
	int waiting_time;
	int remaining_time;
	int leave_time;
};
void ganttchart_p(struct processes* p,int np,int wait_time)
{
	char tabular[3][wait_time];
	int timeline[wait_time];
	int time;	
	
	for(int i = 0; i < wait_time; i++)
		{
			tabular[0][i] = '-';
			tabular[1][i] = ' ';
			tabular[2][i] = '-';
			timeline[i] = 0;
		}
	tabular[1][0] = '|';
	tabular[1][wait_time-1] = '|'; 
	
	int dif;

	time = p[0].burst_time;
	tabular[1][time-1] = '|';
	dif = p[0].burst_time/2;
	tabular[1][dif-1] =p[0].process_id;
	timeline[time-1] = time;
		
	for(int i=1;i<np;i++)
	{
		time += p[i].burst_time;		
		tabular[1][time-1] = '|';
		tabular[1][time-2] = p[i].process_id;
		timeline[time-1] = time;
	}
	
	int i,j;
	int last = p[np-1].burst_time + (np==1 ? 0:p[np-1].waiting_time);
	printf(" ");
	for(i=0; i<np; i++) {
        for(j=0; j<p[i].burst_time; j++) printf("--");
        printf(" ");
    }
    printf("\n|");
    // middle position
    for(i=0; i<np; i++) {
        for(j=0; j<p[i].burst_time-1; j++) printf(" ");
        printf(" %d ", p[i].process_id);
        for(j=0; j<p[i].burst_time-1; j++) printf(" ");
        printf("|");
    }
    printf("\n ");
    // bottom bar
    for(i=0; i<np; i++) {
        for(j=0; j<p[i].burst_time; j++) printf("--");
        printf(" ");
    }
    printf("\n");
    printf("%d ",timeline[0]);
	for(int i = 1; i< wait_time;i++)
	{ 
		if(timeline[i] !=0)
			printf("%d ",timeline[i]);
		else	
			printf("  ");
	}
	printf("\n");
    	
    }
void fcfs(struct processes *p, int np)
{	
	float wait_time ;
	float turn_time ;
	for(int i = 0; i < np; i++)
	{
		p[i].waiting_time = wait_time - p[i].arrival_time;
		p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
		turn_time += p[i].turnaround_time;
		wait_time += p[i].burst_time;
		
	}
	printf("\t ProcessId \t\tArrival \t\tBurst \t\t Turnaround \t\t Waiting \n");
	for(int i = 0; i < np; i++)
	{
		printf("\t %c \t\t\t %d \t\t\t %d \t\t\t %d \t\t\t %d \n",p[i].process_id,p[i].arrival_time,p[i].burst_time,p[i].turnaround_time,p[i].waiting_time);
	}
	float t_time = 0;
	for(int i=0; i<np;i++)
	{
		t_time += p[i].waiting_time;
	}
	float avg_wait = t_time /np;
	float avg_turn = turn_time /np;
	printf("Average waiting time : %f \n",avg_wait);
	printf("Average turnaround time : %f \n",avg_turn);
	ganttchart_p(p,np,wait_time);

}
void sort(struct processes *p ,int np)
{
	struct processes t;
	int shortest;
	for(int i = 0; i < np -1 ;i++) 
	{
		for(int j = 0 ;j < np - i -1; j++)
			{
				if(p[i].arrival_time == p[j].arrival_time)
				{
					for(int k = i ; k < j   ; k++)			
						{
							if(p[k].burst_time  < p[k+1].burst_time)
									shortest = k;
						}
				t = p[shortest];
				p[shortest] = p[j];
				p[j] = t; 
				}
				else if(p[j].arrival_time < p[i].arrival_time)
				{
					t = p[j];
					p[j] = p[i];
					p[i] = t; 
				}									
			}
	}
}
void nonpreemptive(struct processes* p ,int np)
{
	sort(p,np);
	float wait_time ;
	float turn_time ;
	for(int i = 0; i < np; i++)
	{
		// printf(" %d \n",wait_time);
		p[i].waiting_time = wait_time;
		p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
		turn_time += p[i].turnaround_time;
		wait_time += p[i].burst_time;
		
	}
	printf("\t ProcessId \t\tArrival \t\tBurst \t\t Turnaround \t\t Waiting \n");
	for(int i = 0; i < np; i++)
	{
		printf("\t %c \t\t\t %d \t\t\t %d \t\t\t %d \t\t\t %d \n",p[i].process_id,p[i].arrival_time,p[i].burst_time,p[i].turnaround_time,p[i].waiting_time);
	}
	float t_time = 0;
	for(int i=0; i<np;i++)
	{
		t_time += p[i].waiting_time;
	}
	float avg_wait = t_time /np;
	float avg_turn = turn_time /np;
	printf("Average waiting time : %f \n",avg_wait);
	printf("Average turnaround time : %f \n",avg_turn);
	ganttchart_p(p,np,wait_time);


}

void gantt_pre(struct processes *p, int np,char tabular[100],int timeline[100],int wait_time,int ck)
{

	for(int i = 0;i < ck;i++)
		{
			for(int j =0;j< timeline[i];j++)
			{
				printf("-");
			}
		}
	printf("\n");
	printf("|");
	for(int i = 0;i < ck;i++)
	{
		if(tabular[i]!=' ')
		{
			for(int j=0;j< timeline[i]/2;j++)
			{
				printf(" ");
			}
				printf("p%c",tabular[i]);
			for(int j=0;j< timeline[i]/2;j++)
			{
				printf(" ");
			}
			printf("|");
		}
		else
			printf(" ");
	}
	printf("\n");
	for(int i = 0;i < ck;i++)
		{
			for(int j =0;j< timeline[i];j++)
			{
				printf("-");
			}
		}
	printf("\n");
	printf("0");
	for(int i=0;i<ck;i++)
	{
		for(int j=0;j<timeline[i];j++)
		{
			printf(" ");
		}
		printf("%d",timeline[i]);
	}
	
	
}

void preemptive(struct processes *p ,int np)
{
	int shortest = 0;
	int complete = 0; // no of completed processes
	int finish = 0;
	int minimum = 100;
	float wait_time = 0;
	float turn_time = 0;
	char tabular[100];
	int timeline[100];
	int ck = 0;
	
	for(int i = 0;i < 100 ;i++)
	{
		timeline[i] = 0;
		tabular[i] = ' ';
	}
	
	int t = 0; //cpu current time
	int check = 0; // checking if shortest time exists
	for(int i = 0;i < np;i++)
	 p[i].remaining_time = p[i].burst_time;
	 
	while(complete != np)
	{
		for(int j = 0 ; j < np ; j++)
		{	
			if( (p[j].arrival_time <=t) && (p[j].remaining_time < minimum) && (p[j].remaining_time > 0)) 
			{	
					
				
				minimum = p[j].remaining_time;
				//tabular[ck] = p[j].process_id;
				//timeline[ck] = t;
				shortest = j;
				check = 1;
				//ck++;
			}
			
		}
		if(check == 0)
		{
			t++;
			continue;
		}
		
		p[shortest].remaining_time -=1;
		minimum = p[shortest].remaining_time;
		
				
		if(minimum == 0)
			minimum = 100;
		if(p[shortest].remaining_time == 0)
		{
			complete++;
			check = 0 ;
			finish = t + 1;
			tabular[ck] = p[shortest].process_id;
			timeline[ck] = finish;
			ck++;
				
		p[shortest].waiting_time = finish - p[shortest].burst_time - p[shortest].arrival_time;
		
		if( p[shortest].waiting_time < 0)
			p[shortest].waiting_time = 0;
		}
		
		t++;
	}
	for(int i = 0 ; i < np;i++)
		p[i].turnaround_time = p[i].burst_time + p[i].waiting_time;
	
	for(int i = 0; i < np; i++)
	{
		turn_time += p[i].turnaround_time;
		wait_time += p[i].waiting_time;
		
	}
	printf("\t ProcessId \t\tArrival \t\tBurst \t\t Turnaround \t\t Waiting \n");
	
	for(int i = 0; i < np; i++)
	{
		printf("\t %c \t\t\t %d \t\t\t %d \t\t\t %d \t\t\t %d \n",p[i].process_id,p[i].arrival_time,p[i].burst_time,p[i].turnaround_time,p[i].waiting_time);
	}
	
	float avg_wait = wait_time /np;
	float avg_turn = turn_time /np;
	printf("Average waiting time : %f \n",avg_wait);
	printf("Average turnaround time : %f \n",avg_turn);
	
	gantt_pre(p,np,tabular,timeline,wait_time,ck);	
}			
void main()
{
	int no_of_processes;
	printf("Enter number of processes \n");
	scanf("%d",&no_of_processes);
	int choice;
	struct processes *p = malloc(sizeof(struct processes)*no_of_processes);
	
	for(int i = 0; i < no_of_processes; i++)
	{
		printf("Enter process ID \n");
		scanf(" %c",&p[i].process_id);
		printf("Enter Burst time \n");
		scanf("%d",&p[i].burst_time);
		printf("Enter arrival time \n");
		scanf("%d",&p[i].arrival_time);
	}
	while(choice!=4)
	{
	printf("\t\t Main Menu \n");
	printf("\t 1. First Come First Serve(FCFS)\n");
	printf("\t 2. SJF (preemptive)\n");
	printf("\t 3. SJF (Non-Preemptive)\n");
	printf("\t 4. Exit\n");
	printf("Enter choice \n");
	scanf("%d",&choice);
	switch(choice)
		{
			case 1: fcfs(p,no_of_processes);
			        break;
			case 2: preemptive(p,no_of_processes);
			        break;
			case 3: nonpreemptive(p, no_of_processes);
			        break;
		}
	}

 }

