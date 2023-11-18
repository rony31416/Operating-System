#include<iostream>
using namespace std;
int main() {
	double n,bt[200],wt[200],tat[200],avwt = 0,avtat = 0;
	int i,j;
	cout<<"Enter total number of processes:";
	cin>>n;
	cout<<"\nEnter Process Burst Time\n";
	for (i=0;i<n;i++) {
		cout<<"P["<<i+1<<"]:";
		cin>>bt[i];
	}
	wt[0]=0;
	//waiting time for first process is 0
	//calculating waiting time
	for (i=1;i<n;i++) {
		wt[i]=0;
		for (j=0;j<i;j++)
		            wt[i]+=bt[j];
	}
	cout<<"\nProcess  \tBurstTime\tWaitingTimet\tTurnaroundTime";
	//calculating turnaround time
	for (i=0;i<n;i++) {
		tat[i]=bt[i]+wt[i];
		avwt+=wt[i];
		avtat+=tat[i];
		cout<<"\nP["<<i+1<<"]"<<"\t\t"<<bt[i]<<"\t\t"<<wt[i]<<"\t\t"<<tat[i]<<"\n";
	}

	cout<<"\nTotal watting time = "<<avwt<<"\n";
	avwt/=(n/1.0);
	avtat/=(n/1.0);
	cout<<"Average Waiting Time:"<<avwt;
	cout<<"\nAverage Turnaround Time:"<<avtat;
	return 0;
}
