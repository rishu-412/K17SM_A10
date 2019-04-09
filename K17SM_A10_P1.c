#include<stdio.h>
#include<stdlib.h>
int time = 0;
int sum1;
struct Process
{
		int Process_id, Arrival_time, Burst_time, Waiting_time, TurnAround_time, Queue_no;
		Process(){
			Process_id = 0; Arrival_time = 0; Burst_time = 0; Waiting_time = 0; TurnAround_time = 0; Queue_no = 0;
		}
};
int compare(const void *s1, const void *s2){
	struct Process *p1 = (struct Process *)s1;
	struct Process *p2 = (struct Process *)s2;
	int temp = p1->Arrival_time - p2->Arrival_time;
	if(temp == 0)
		return (p1->Process_id - p2->Process_id);
	else
		return temp;
		
}
void Queue1_at_time(Process p[], int i);
int Shortest_job(Process p[], int n);
int sum_of_burst(Process p[], int n);
int sum_of_burst(Process p[], int n)
{
	int sum = 0;
	for(int i= 0; i < n; i++)
		sum += p[i].Burst_time;
	return sum; 
}
int Round_job(Process p[], int n)
{
	printf("\nReady queue2: ");
	int i = 0;
	while(time <= sum1 && i < n){
			if(p[i].Burst_time-2 >= 0 && p[i].Arrival_time <= time && p[i].Queue_no == 2){
				p[i].Waiting_time += time - p[i].Arrival_time;
				p[i].Burst_time -=2;
				time = time +2;
				p[i].Arrival_time = time;
				i++;
			}
			else if(p[i].Burst_time - 1 >= 0 && p[i].Arrival_time <= time && p[i].Queue_no == 2){
				p[i].Waiting_time += time - p[i].Arrival_time;
				p[i].Burst_time -=1;
				time = time +1;
				p[i].Arrival_time = time;
				i++;
			}
			else{//time++;}
		}
			if(i >= n && time <=sum1){
				i = 0;
			}
	}
}
void Queue_at_time(Process p[], int n){
	printf("\nPID\t CTime\t Wtime\n");
	for(int i = 0;i < n; i++)
		printf("%d\t %d\t %d\n",p[i].Process_id,p[i].Arrival_time,p[i].Waiting_time);
}
int main()
{
		int n;
		printf("Enter the number of proesses: ");
		scanf("%d",&n);
		struct Process p[n];
		
		for(int i = 0; i < n; i++)
		{
				p[i].Process_id = i+1;
				printf("Enter the Process Arrival Time for %d: ",i+1);
				scanf("%d", &p[i].Arrival_time);
				printf("Enter the Process Burst Time for %d: ",i+1);
				scanf("%d", &p[i].Burst_time);
				printf("Enter the Process Queue_no for %d: ",i+1);
				scanf("%d", &p[i].Queue_no);			
		}
		qsort((void *)p,n,sizeof(struct Process),compare);
		sum1 = sum_of_burst(p,n);
		Round_job(p,n);
		Queue_at_time(p, n);
}
