#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
typedef struct process{
	int pid;
	int arrival_time;
	int burst_time;
	int completion_time;
	int tat;
	int waiting_time;
}Process;
void print(Process processes[], int n){
	printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
	for(int i=0;i<n;i++){
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",processes[i].pid,processes[i].arrival_time,processes[i].burst_time,processes[i].completion_time,processes[i].tat,processes[i].waiting_time);
	}


}
void fcfs(Process processes[], int n){
	int curr_time=0;
	for(int i=0;i<n;i++){
		if(curr_time<processes[i].arrival_time){
			curr_time=processes[i].arrival_time;
		}
	curr_time+=processes[i].burst_time;
	processes[i].completion_time=curr_time;
	processes[i].tat=processes[i].completion_time-processes[i].arrival_time;
	processes[i].waiting_time=processes[i].tat-processes[i].burst_time;
	}
	print(processes,n);
}
void sjf_nonpre(Process processes[], int n){
	int curr_time=0;
	int completion[n];
	int completed=0; 
	for(int i=0;i<n;i++){
	completion[i]=0;
	//none of the processes have been completed.
	}
while(completed!=n){
int shortest=-1;
int min_burst=9999;
	for(int i=0;i<n;i++){
		
	if(processes[i].arrival_time<=curr_time && completion[i]==0){
		if(processes[i].burst_time<min_burst){
		shortest=i;
		min_burst=processes[i].burst_time;
	}
else if(processes[i].burst_time==min_burst && processes[i].arrival_time<processes[shortest].arrival_time){
shortest=i;
}
	}
}//I loop
if(shortest==-1){
	curr_time++;
}
else{
	curr_time+=processes[shortest].burst_time;
	processes[shortest].completion_time=curr_time;
	processes[shortest].tat=processes[shortest].completion_time-processes[shortest].arrival_time;
	processes[shortest].waiting_time=processes[shortest].tat-processes[shortest].burst_time;	
	completion[shortest]=1;
	completed++;
}

	}////j loop
print(processes,n);

}
void sjf_pre(Process processes[], int n){
	int curr_time=0;
	int remaining_time[n];
	int completion[n];
	int completed=0;
	for(int i=0;i<n;i++){
	remaining_time[i]=processes[i].burst_time;
	completion[i]=0;
}
while(completed<n){
	int shortest=-1;
	int min_rem=9999;
	//find out the min remaining time
	for(int i=0;i<n;i++){
		if(processes[i].arrival_time<=curr_time && completion[i]==0){
			if(remaining_time[i]<min_rem){
				shortest=i;
				min_rem=remaining_time[i];
}
		else if(remaining_time[i]==min_rem && processes[i].arrival_time<processes[shortest].arrival_time){
			shortest=i;
}//else if

}//if
}//i loop
//if there is no min then 
if(shortest==-1){
	curr_time++;
	continue;
}
remaining_time[shortest]--;
curr_time++;
if(remaining_time[shortest]==0){
	processes[shortest].completion_time=curr_time;
	processes[shortest].tat=processes[shortest].completion_time-processes[shortest].arrival_time;
	processes[shortest].waiting_time=processes[shortest].tat-processes[shortest].burst_time;
	completion[shortest]=1;
	completed++;

}
}//while loop ends
	print(processes,n);
}//function ends



int main(){
	Process processes[]={
	{1, 0, 8},
        {2, 0, 4},
        {3, 2, 9}
};
	int n=sizeof(processes)/sizeof(processes[0]);
	printf("shortest job first  pre:\n");
	sjf_pre(processes,n);
	return 0;

}
