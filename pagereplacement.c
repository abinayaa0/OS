#include <stdio.h>
#include <stdlib.h>
#define FRAME_SIZE 3
void printframes(int frames[], int size){
    for(int i = 0; i < size; i++) {
        if(frames[i] != -1) {
            printf("%d ", frames[i]);  // Print filled frames
        } else {
            printf("_ ");  // Print _ for empty slots
        }
    }
    printf("\n");
}
void lru(int pages[], int n){
	int frames[FRAME_SIZE];
	for(int i=0;i<FRAME_SIZE;i++){
		frames[i]=-1;
	}
	int pagefault=0;
	for(int i=0;i<n;i++){
		int page=pages[i];
		int found=0;
		for(int j=0;j<FRAME_SIZE;j++){
		if(frames[j]==page){
		found=1;
		break;
		}

		}
		if(found==0){
		int lruindex=0;
		int lrutime=n;
		for(int j=0;j<FRAME_SIZE;j++){
			int k;
			for(k=i-1;k>=0;k--){
				if(frames[j]==pages[k]){
					break;
				}

			}
			if(k<lrutime){
				lrutime=k;
				lruindex=j;
			}
		}
		frames[lruindex]=page;
		pagefault++;

		}
	printframes(frames,FRAME_SIZE);
		
	}
	printf("The total number of page faults is: %d",pagefault);
	

}
void optimal(int pages[], int n){
	int frames[FRAME_SIZE];
	for(int i=0;i<FRAME_SIZE;i++){
		frames[i]=-1;
	}
	int pagefault=0;
	for(int i=0;i<n;i++){
	int page=pages[i];
	int found=0;
	for(int j=0;j<FRAME_SIZE;j++){
		if(frames[j]==page){
			found=1;
			break;
		}
	}
	if(found==0){
		int replacementidx=0;
		int farthest=-1;
		for(int j=0;j<FRAME_SIZE;j++){
			int k;
			for(k=i+1;k<n;k++){
				if(frames[j]==pages[k]){
					break;
				}

			}
			if(k>farthest){
				farthest=k;
				replacementidx=j;
			}
		}
	frames[replacementidx]=page;
	pagefault++;

	}//found==0
	printframes(frames,FRAME_SIZE);
	
	}
	printf("The total number of page faults is:%d\n",pagefault);

}
// FIFO page replacement
void fifo(int pages[],int n){
	//initialise all the frames as -1 to denote empty.
	int frames[FRAME_SIZE];
	for(int i=0;i<FRAME_SIZE;i++){
		frames[i]=-1;
	}
	int nextframe=0;
	int pagefault=0;
	for(int i=0;i<n;i++){
	//get the current page from pages.
	int page=pages[i];
	int found=0;
	for(int j=0;j<FRAME_SIZE;j++){
		if(frames[j]==page){
			found=1;
			break;
		}
	}
	if(found==0){
	//if page not found in frame
	frames[nextframe]=page;
	nextframe=(nextframe+1)%FRAME_SIZE;
	pagefault++;

	}
	printframes(frames,FRAME_SIZE);
//inside the loop so prints every time.

	}
	printf("Total page faults:%d\n",pagefault);

}

//LEAST REPLACEMENT
//MOST REPLACEMENT
//OPTIMAL SOMETHING

int main(){
	int pages[] = {0, 1, 2, 1, 3, 0, 1, 2, 0, 3}; 	
	int n=sizeof(pages)/sizeof(pages[0]);
	optimal(pages,n);

return 0;
}
