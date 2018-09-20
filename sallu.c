#include<stdio.h>
#include<stdlib.h>
struct input
{
	int at;
	int bt;
}p[5]={{9,4},{0,8},{6,10},{3,4},{4,2}};
struct output
{
	int pr;
	int st;
	int et;

}gc[50];
int ct=0;
int k=0;
int ar[5]={0};
int cm[5]={0};
int cet[5];
int get_comp_no()
{
	int t=0;
	for(int i=0;i<5;i++)
	{
		if(cm[i]==1)
			t++;
		
	}
	return t;
}
int who_ex()
{
	int min=-1;
	for(int i=0;i<5;i++)
	{
		if(p[i].at<=ct)
		ar[i]=1;	
	}
	for(int i=0;i<5;i++)
	{
		if(ar[i]==1 && cm[i]==0)
		{
			if(min==-1)
			{
				min=i;
			}
			else
			{
				if(cet[i]<cet[min] || (cet[i]== cet[min] && p[i].at<p[min].at))
				{
					min=i;
				
				}
				
			
			}
	
		}
	}
	return min;
}
int main()
{
	for(int i=0;i<5;i++)
	{
		cet[i]=p[i].bt;
	}
	while(get_comp_no()<5)
	{
		int pr=who_ex();
			gc[k].pr=pr;
			gc[k].st=ct;
			gc[k].et=ct+1;
			ct++;
			cet[pr]--;
			if(cet[pr]==0)
				cm[pr]=1;
				printf("V= %d %d %d %d\n",gc[k].pr,gc[k].st,gc[k].et,k);
			k++;
			
	
	}
	return 0;
}