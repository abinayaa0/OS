#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define MAX 10
#define PRO 5
#define RES 3
int alloc[PRO][RES]={
    {0, 1, 0},  // Process 0 has 0 of resource 1, 1 of resource 2, and 0 of resource 3
    {2, 0, 0},  // Process 1 has 2 of resource 1, 0 of resource 2, and 0 of resource 3
    {3, 0, 2},  // Process 2 has 3 of resource 1, 0 of resource 2, and 2 of resource 3
    {2, 1, 1},  // Process 3 has 2 of resource 1, 1 of resource 2, and 1 of resource 3
    {0, 0, 2}   //
};
int max[PRO][RES]={  { 7, 5, 3 }, 
                      { 3, 2, 2 }, 
                      { 9, 0, 2 }, 
                      { 2, 2, 2 }, 
                      { 4, 3, 3 }
 }; 
int avail[RES]={3,3,2};

void calcneed(int need[PRO][RES]){
	for(int i=0;i<PRO;i++){
		for(int j=0;j<RES;j++){
		need[i][j]=max[i][j]-alloc[i][j];
	}
	}
}
bool isSafe(int alloc[PRO][RES], int max[PRO][RES],int avail[RES],int processes[PRO]){
		int need[PRO][RES];
		calcneed(need);
		bool finish[PRO]={0};
		int safeseq[PRO];
		int work[RES];
		for(int i=0;i<RES;i++){
			work[i]=avail[i];
			}
		int count=0;
		while(count<PRO){
			bool found=false;
			for(int p=0;p<PRO;p++){
				if(!finish[p]){
					int j;
					for(j=0;j<RES;j++){
						if(need[p][j]>work[j]){
							break;
							}
					}
				if(j==RES){
					for(int k=0;k<RES;k++){
						work[k]+=alloc[p][k];
					}
					finish[p]=1;
					//safeseq[count++]=p;
					found=true;
				}

				}//finish p if

				}//p loop
			if(!found){
				printf("The system is not in safe condition");
				return false;

			}
			}//while loop
		for(int i=0;i<PRO;i++){
			printf("%d ",safeseq[i]);

		}
		return true;

}
int main(){
	int process[]={0,1,2,3,4};
	isSafe(alloc,max,avail,process);
	return 0;
}
