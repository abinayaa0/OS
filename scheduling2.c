#include <stdlib.h>
#include <stdio.h>
typedef struct processes{
	int pid;
	int arrival_time;
	int burst_time;
	
	int priority;
	int remaining_time;
	int completion_time;
	int tat;
	int waiting_time;

}Process;
void print(Process processes[], int n){//
	printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
	for(int i=0;i<n;i++){
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",processes[i].pid,processes[i].arrival_time,processes[i].burst_time,processes[i].completion_time,processes[i].tat,processes[i].waiting_time);
	}


}

void priority(Process processes[], int n){
	int completed=0;
	int completion[n];
	int remaining_time[n];
	int curr_time=0;
	for(int i=0;i<n;i++){
	completion[i]=0;
	remaining_time[i]=processes[i].burst_time;
	}


while(completed<n){
int shortest=-1;
int highest_priority=9999;
	for(int i=0;i<n;i++){	
		if(processes[i].arrival_time<=curr_time && completion[i]==0){
			if(processes[i].priority<highest_priority){
				shortest=i;
				highest_priority=processes[i].priority;

			}
		else if(processes[i].priority==highest_priority && processes[i].arrival_time<processes[shortest].arrival_time){
			shortest=i;
		}

	}
}//for loop ends
if(shortest==-1){
	curr_time++;
	continue;
} 
remaining_time[shortest]--;
curr_time++;
if(remaining_time[shortest]==0){
	//curr_time+=processes[shortest].burst_time; //important dont forget.
	processes[shortest].completion_time=curr_time;	
	processes[shortest].tat=processes[shortest].completion_time-processes[shortest].arrival_time;
	processes[shortest].waiting_time=processes[shortest].tat-processes[shortest].burst_time;
	completed++;
	completion[shortest]=1;
}
	
	
}//while loop ends

	print(processes,n);
}//function ends
void round_robin(Process processes[], int n, int quantum){
	int completed=0;
	int curr_time=0;
	int completion[n];
	for(int i=0;i<n;i++){
		completion[i]=0;
		processes[i].remaining_time=processes[i].burst_time;
	}

while(completed<n){
	int done_in_this_cycle=0;
	for(int i=0;i<n;i++){
		if(processes[i].arrival_time <=curr_time && completion[i]==0){
			done_in_this_cycle=1;
			if(processes[i].remaining_time>quantum){
				curr_time+=quantum;
				processes[i].remaining_time-=quantum;
			}
			else{
			curr_time+=processes[i].remaining_time;
			processes[i].completion_time=curr_time;
			processes[i].tat=processes[i].completion_time-processes[i].arrival_time;
			processes[i].waiting_time=processes[i].tat-processes[i].burst_time;
			processes[i].remaining_time=0;
			completed++;
			completion[i]=1;
			}
		}
	if(done_in_this_cycle==0){
		curr_time++;
		continue;
	}

	}


}
print(processes,n);

}

int main(){
	Process processes[] = {
        {1, 0, 8, 2},
        {2, 1, 4, 1},
        {3, 2, 9, 3}
    };
	int n=sizeof(processes)/sizeof(processes[0]);
	round_robin(processes,n,3);
return 0;
}
