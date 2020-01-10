#include<iostream>
#include<algorithm>
#include<string>
#include<map>
#include<vector>
using namespace std;

struct node {
	int addr;
	int data;
	int next;
}a[100005];

map<int,node> mm;

int main() {
	int start,n,k;
	cin >> start >> n >> k;
	for (int i=0;i<n;i++) {
		cin >> a[i].addr >> a[i].data >> a[i].next;
		mm.insert(make_pair(a[i].addr, a[i]));
	}
	vector<int> addList;
	int tmp=start;
	addList.push_back(tmp);
	while (tmp!=-1){
		tmp = mm[tmp].next;
		addList.push_back(tmp);
	}
//	for (int i=0;i<addList.size();i++) {
//		printf("%05d ", addList[i]);
//	}
//	printf("\n");
	n = addList.size()-1;
	int poi = k;
	if (n%k==0) {
		poi = n-k;
	}
	else {
		poi = n-n%k;
		for (int i=poi;i<n-1;i++) {
			if (mm[addList[i]].addr!=-1) {
				printf("%05d ", mm[addList[i]].addr);
			}
			else {
				printf("-1 ");
			}
			printf("%d ", mm[addList[i]].data);
			if (mm[addList[i]].next!=-1) {
				printf("%05d\n", mm[addList[i]].next);
			}
			else {
				printf("-1\n");
			}
		}
		if (mm[addList[n-1]].addr!=-1) {
			printf("%05d ", mm[addList[n-1]].addr);
		}
		else {
			printf("-1 ");
		}
		printf("%d ", mm[addList[n-1]].data);
		poi -= k;
		if (poi>=0) {
			if (mm[addList[poi]].addr!=-1) {
				printf("%05d\n", mm[addList[poi]].addr);
			}
			else {
				printf("-1\n");
			}
		}
	}
	while (poi>=0) {
		for (int i=poi;i<poi+k-1;i++) {
			if (mm[addList[i]].addr!=-1) {
				printf("%05d ", mm[addList[i]].addr);
			}
			else {
				printf("-1 ");
			}
			printf("%d ", mm[addList[i]].data);
			if (mm[addList[i]].next!=-1) {
				printf("%05d\n", mm[addList[i]].next);
			}
			else {
				printf("-1\n");
			}
		}
		if (mm[addList[poi+k-1]].addr!=-1) {
			printf("%05d ", mm[addList[poi+k-1]].addr);
		}
		else {
			printf("-1 ");
		}
		printf("%d ", mm[addList[poi+k-1]].data);
		poi = poi-k;
		if (poi>=0) {
			if (mm[addList[poi]].addr!=-1) {
				printf("%05d\n", mm[addList[poi]].addr);
			}
			else {
				printf("-1\n");
			}
		}
	}
	printf("-1\n");
	return 0;
}
