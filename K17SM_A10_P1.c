#include<stdio.h>
#include<stdlib.h>
int time = 0, time1 = 0, time2 = 0, num1 = 0, num2 = 0;
int sum1, sumQ1, sumQ2;
struct Process
{
		int Process_id, Arrival_time, Burst_time, Waiting_time, TurnAround_time, Queue_no, Completion_time;
		Process(){
			Process_id = 0; Arrival_time = 0; Burst_time = 0; Waiting_time = 0; TurnAround_time = 0; Queue_no = 0; Completion_time = 0;
		}
};

void Queue_at_time(Process p[], int i);				//Prints the Table with Waiting Time, Arrval Time, Completion time 
int Round_job(Process p[], int n);				//Round robin Scheduling algorithm
int Shortest_job(Process p[], int n);				//Shortest Job First Algorithm
int sum_of_burst(Process p[], int n);				//returns the sum of Burst time
int compare(const void *s1, const void *s2);			//used for Qsort algorithm
int available_jobs(Process p[], int n, int j);			//total jobs Available at a particular time
void calc_turnAround(Process p[], Process b[], int n);		//updates the backup object with TurnAround time

int main(){							// main() function to call the above functions
	int n;
	printf("Enter the number of proesses: ");
	scanf("%d",&n);
	struct Process p[n], backup[n];
	
	for(int i = 0; i < n; i++)
	{
			p[i].Process_id = i+1;
			backup[i].Process_id = p[i].Process_id;
			printf("Enter the Process Arrival Time for %d: ",i+1);
			scanf("%d", &p[i].Arrival_time);
			backup[i].Arrival_time = p[i].Arrival_time;
			printf("Enter the Process Burst Time for %d: ",i+1);
			scanf("%d", &p[i].Burst_time);
			backup[i].Burst_time = p[i].Burst_time;
			printf("Enter the Process Queue_no for %d: ",i+1);
			scanf("%d", &p[i].Queue_no);		
			backup[i].Queue_no = p[i].Queue_no;	
			printf("\n");
	}
	sum1 = sum_of_burst(p,n);		
	qsort((void *)p,n,sizeof(struct Process),compare);
	printf("\nGantt Chart: ");
	if(available_jobs(p,n,1) > 0)
		Shortest_job(p,n);
	else if(available_jobs(p,n,2) > 0)
		Round_job(p,n);
	else{}
	calc_turnAround(p,backup,n);
	Queue_at_time(backup, n);
	double avg_WT = 0;
	double avg_TA = 0;
	for(int i = 0; i < n; i++){
		avg_WT += backup[i].Waiting_time;
		avg_TA +=backup[i].TurnAround_time;
	}
	printf("\nAverage Waiting time: %lf", avg_WT/n);
	printf("\nAverage Turn Around time: %lf", avg_TA/n);
}

void calc_turnAround(Process p[], Process q[], int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++)
			if(p[i].Process_id == q[j].Process_id){
				q[i].TurnAround_time = p[i].Waiting_time + q[j].Burst_time;
				q[i].Completion_time = p[i].Arrival_time;
				q[i].Waiting_time = p[i].Waiting_time;
			}
		
	}	
}

int available_jobs(Process p[], int n, int j){
	int sum = 0;
	for(int i =0; i < n; i++){
		if(p[i].Arrival_time <= time && p[i].Burst_time >0 && p[i].Queue_no == j)
			sum++;
	}
	return sum;
}

int sum_of_burst(Process p[], int n){
	int sum = 0;
	for(int i= 0; i < n; i++)
		sum += p[i].Burst_time;
	return sum; 
}

int compare(const void *s1, const void *s2){
	struct Process *p1 = (struct Process *)s1;
	struct Process *p2 = (struct Process *)s2;
	int temp = p1->Arrival_time - p2->Arrival_time;
	if(temp == 0)
		return (p1->Process_id - p2->Process_id);
	else
		return temp;
		
}

int Round_job(Process p[], int n){
	int i = 0; int timeq = 2;
	int flag = 0;
	while(i < n){
			timeq = 2;
			while(timeq--){
				if(p[i].Burst_time - 1 >= 0 && p[i].Arrival_time <= time && p[i].Queue_no == 2){
						p[i].Waiting_time += time - p[i].Arrival_time;
						p[i].Burst_time -=1;
						time = time +1;
						p[i].Arrival_time = time;
						if(time > sum1)
							p[i].Arrival_time = time - 1;
						else			
							p[i].Arrival_time = time;
						printf("%d ",p[i].Process_id);
						
						if(available_jobs(p,n,1) > 0){
							flag = 1;
							break;
							}		
					}
			}
			if(flag == 0)
			{
				i++;
			}
			else
				Shortest_job(p,n);
		
			if(i >= n){
				i = 0;
			}
			if(available_jobs(p,n,2) == 0){	
							return 0;
			}
	}
	return 0;
}

int Shortest_job(Process p[], int n){
	int small, small_process = 0;
	while(time != sum1){
		small = 9999;
		for(int i = 0; i < n; i++){
			if(small > p[i].Burst_time && p[i].Burst_time > 0 && p[i].Arrival_time <= time && p[i].Queue_no == 1 ){
				small_process = i;
				small = p[i].Burst_time;
			}
			else if(small == p[i].Burst_time && p[i].Burst_time > 0 && p[i].Arrival_time <= time && p[i].Queue_no == 1){
					if(small_process > i ){
							small_process = i;
							small = p[i].Burst_time;
						}
					}
			else{}
		}
		
		p[small_process].Waiting_time += time - p[small_process].Arrival_time;
		--p[small_process].Burst_time;
		printf("%d ",p[small_process].Process_id);
		time++;
		if(time > sum1)
			p[small_process].Arrival_time = time - 1;
		else
			p[small_process].Arrival_time = time;
		
		if(!(available_jobs(p,n,1) > 0) && available_jobs(p,n,2) > 0 )
			Round_job(p,n);
	}
	return 0;
}

void Queue_at_time(Process p[], int n){
	printf("\n\nPID\t Atime\t Btime\t Wtime\t TAtime\t CTime\n");
	for(int i = 0;i < n; i++)
		printf("%d\t %d\t %d\t %d\t %d\t %d\n",p[i].Process_id,p[i].Arrival_time,p[i].Burst_time,p[i].Waiting_time,p[i].TurnAround_time,p[i].Completion_time);
}
