#include<stdio.h>
#include<stdlib.h>
struct processes
{
	int arrival_time;
	int burst_time;
	int process_id;
	int priority;
	int turnaround_time;
	int waiting_time;
	int remaining_time;
	int complete_time;
	int leave_time;
	int result_atime;
	int start_time;
};
void ganttchart(int time_seq[100],int ids[100],int k)
{
	printf("\t\t");
	int diff;
	
	// top line
	for(int i=1;i<k;i++)
	{
		diff = (time_seq[i] - time_seq[i-1])  ;
		for(int j=0;j<diff/2;j++)
			printf("--");
		printf("--");
		for(int j=0;j<diff/2;j++)
			printf("--");
	
	}
	printf("\n");
	printf("\t\t");
	printf("|");
	// middle
	for(int i=1;i<k;i++)
	{
		diff = (time_seq[i] - time_seq[i-1])/2;
		for(int j=0;j<diff;j++)
			printf(" ");
		printf("P%d",ids[i-1]);
		for(int j=0;j<diff;j++)
			printf(" ");
		printf("|");
	}
	printf("\n");
	printf("\t\t");
	
	//bottom
	for(int i=1;i<k;i++)
	{
		diff = (time_seq[i] - time_seq[i-1])  ;
		for(int j=0;j<diff/2;j++)
			printf("--");
		printf("--");
		for(int j=0;j<diff/2;j++)
			printf("--");

	}
	printf("\n");
	printf("\t\t");
	printf("0");
	for(int i=1;i<k;i++)
	{
		diff = (time_seq[i] - time_seq[i-1]);
		for(int j=0;j<diff;j++)
			printf("  ");
		printf("%d",time_seq[i]);
	}
	printf("\n");
	
}
void ganttchart_np(struct processes* p,int np,int wait_time)
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
			printf("%d",timeline[i]);
		else	
			printf("   ");
	}
	printf("\n");
    	
    }
void round_robin(struct processes *p,int np,int slice)
{
	float wait_time;
	float turn_time;
	int time_sequence[100];
	int ids[100];
	int k = 0;
	int idc = 0;
	for(int i = 0;i < np;i++)
	{
		p[i].remaining_time = p[i].burst_time;
		p[i].leave_time = p[i].arrival_time;
	}
	int completed =0;
	int system_time = 0;
	time_sequence[k++] = system_time;
	ids[idc++] =p[0].process_id;
	while(completed != np)
	{
		for(int i=0;i<np;i++)
		{
			if(p[i].remaining_time != 0)
			{
				if(p[i].remaining_time > slice)
				{
					p[i].remaining_time -= slice;
					p[i].waiting_time += system_time - p[i].leave_time;
					system_time += slice;
					time_sequence[k++] = system_time;
					p[i].leave_time = system_time;
					ids[idc++] = p[i].process_id;
				}
				else if(p[i].remaining_time <= slice)
				{
					p[i].waiting_time += system_time - p[i].leave_time;
					system_time += p[i].remaining_time;
					p[i].remaining_time = 0;
					p[i].complete_time = system_time;
					time_sequence[k++] = system_time;
					ids[idc++] = p[i].process_id;
					completed++;
				}
			}
			else
				continue;
		}
	}
	for(int i=0;i<np;i++)
		p[i].turnaround_time = p[i].complete_time - p[i].arrival_time;
	for(int i=0;i<np;i++)
	{
		wait_time+= p[i].waiting_time;
		turn_time += p[i].turnaround_time;
	}
	printf("\t ProcessId \t\tArrival \t\tBurst \t\t Turnaround \t\t Waiting \n");
	
	for(int i = 0; i < np; i++)
	{
		printf("\t %d \t\t\t %d \t\t\t %d \t\t\t %d \t\t\t %d \n",p[i].process_id,p[i].arrival_time,p[i].burst_time,p[i].turnaround_time,p[i].waiting_time);
	}
	
	float avg_wait = wait_time /np;
	float avg_turn = turn_time /np;
	printf("Average waiting time : %f \n",avg_wait);
	printf("Average turnaround time : %f \n",avg_turn);									

	printf("\n\n\n ");
	
	ganttchart(time_sequence,ids,k);	
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
					
					if(p[i].priority == p[j].priority)
					{
						for(int k = i ; k < j   ; k++)			
						{
							if(p[k].process_id  < p[k+1].process_id)
									shortest = k;
						}
						t = p[shortest];
						p[shortest] = p[j];
						p[j] = t; 
					}
					else
					{
						for(int k = i ; k < j   ; k++)			
						{
							if(p[k].priority  < p[k+1].priority)
									shortest = k;
						}
						t = p[shortest];
						p[shortest] = p[j];
						p[j] = t; 
					}
				}
				else if(p[j].arrival_time > p[j+1].arrival_time)
				{
					t = p[j+1];
					p[j+1] = p[j];
					p[j] = t; 
				}									
			}
	}
}

void nonpreemptive_priority(struct processes* p ,int np)
{
	sort(p,np);
	float wait_time ;
	float turn_time ;
	for(int i = 0; i < np; i++)
	{
		p[i].waiting_time = wait_time - p[i].arrival_time;
		wait_time += p[i].burst_time;
	 p[i].turnaround_time = p[i].burst_time + p[i].waiting_time;
	 turn_time+= p[i].turnaround_time;
	}
	 	
	printf("\t ProcessId \t\tArrival \t\tBurst \t\t Turnaround \t\t Waiting \n");
	for(int i = 0; i < np; i++)
	{
		printf("\t %d \t\t\t %d \t\t\t %d \t\t\t %d \t\t\t %d \n",p[i].process_id,p[i].arrival_time,p[i].burst_time,p[i].turnaround_time,p[i].waiting_time);
	}
	float ttime = 0;
	for(int i=0;i<np;i++)
	{	
	ttime+= p[i].waiting_time;
	}
	float avg_wait = ttime /np;
	float avg_turn = turn_time /np;
	printf("Average waiting time : %f \n",avg_wait);
	printf("Average turnaround time : %f \n",avg_turn);
	ganttchart_np(p,np,wait_time);

}



void preemptive_priority(struct processes *p ,int np)
{
	float wait_time;
	float turn_time;
	int time_sequence[100];
	int ids[100];
	int k = 0;
	int idc = 0;
	for(int i = 0;i < np;i++)
	{
		p[i].remaining_time = p[i].burst_time;
		p[i].leave_time = p[i].arrival_time;
	}
	sort(p,np);
	int completed =0;
	int system_time = 0;
	int j
	time_sequence[k++] = system_time;
	ids[idc++] =p[0].process_id;
	int high_priority =0;
	int memory = 0;
		
		
}			
void main()
{
	int no_of_processes;
	int time_slice;
	printf("Enter number of processes \n");
	scanf("%d",&no_of_processes);
	int choice;
	struct processes *p = malloc(sizeof(struct processes)*no_of_processes);
	
	for(int i = 0; i < no_of_processes; i++)
	{
		printf("Enter process ID \n");
		scanf("%d",&p[i].process_id);
		printf("Enter Burst time \n");
		scanf("%d",&p[i].burst_time);
		printf("Enter arrival time \n");
		scanf("%d",&p[i].arrival_time);
		printf("Enter priority \n");
		scanf("%d",&p[i].priority);
	}
	while(choice!=4)
	{
	printf("\t\t Main Menu \n");
	printf("\t 1. Round robin\n");
	printf("\t 2. Priority (preemptive)\n");
	printf("\t 3. Non Priority (Non-Preemptive)\n");
	printf("\t 4. Exit\n");
	printf("Enter choice \n");
	scanf("%d",&choice);
	switch(choice)
		{
			case 1: printf("Enter time slice \n");
			        scanf("%d",&time_slice);
			        round_robin(p,no_of_processes,time_slice);
			        break;
			case 2: preemptive_priority(p,no_of_processes);
			        break;
			case 3: nonpreemptive_priority(p, no_of_processes);
			        break;
		}
	}

}

