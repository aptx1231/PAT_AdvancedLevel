#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct node{
	char name[22];
	char begin[12];
	char end[12];
	double cost;
}a[1009];

struct input{
	char name[20];
	char time[20];
	int onoff;
}in[1009];

int v[25];

int com(const void *a,const void *b)
{
	if(strcmp(((const struct input*)a)->name,((const struct input*)b)->name)>0){
		return 1;
	}
	else if(strcmp(((const struct input*)a)->name,((const struct input*)b)->name)<0){
		return -1;
	}
	else{
		if(strcmp(((const struct input*)a)->time,((const struct input*)b)->time)>0){
			return 1;
		}
		else{
			return -1;
		}
	}
}

int main()
{
	int i,j;
	for(i=0;i<24;i++){
		scanf("%d",&v[i]);
	}
	int n;
	scanf("%d",&n);
	getchar();
	char s[20];
	for(i=0;i<n;i++){
		scanf("%s %s %s",in[i].name,in[i].time,s);
		if(s[1]=='n') in[i].onoff=1;
		if(s[1]=='f') in[i].onoff=0;
	}
	qsort(in,n,sizeof(struct input),com);
	for(i=0;i<n;i++){
		printf("%s %s %d\n",in[i].name,in[i].time,in[i].onoff);
	}
	return 0;
} 
