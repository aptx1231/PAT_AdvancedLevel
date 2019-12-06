#include<iostream>
#include<algorithm> 
#include<vector>
#include<cstdio>
using namespace std;

int a[1005];
int n;

void judge() {
	int flag;
	if (a[1] > a[2]) {
		flag = 1;  //大顶堆 
	}
	else if (a[1] < a[2]) {
		flag = -1;  //小顶堆 
	}
	else {
		flag = 0;  //暂时无法判定 
	}
	for (int i=1;i<=n;i++) {
		if (2*i <= n) {
			if (flag==1 && a[i]<a[2*i]) {
				flag = -2; //不是堆 
			}
			if (flag==-1 && a[i]>a[2*i]) {
				flag = -2; //不是堆 
			} 
		} 
		if (2*i+1 <= n) {
			if (flag==1 && a[i]<a[2*i+1]) {
				flag = -2; //不是堆 
			}
			if (flag==-1 && a[i]>a[2*i+1]) {
				flag = -2; //不是堆 
			} 
		} 
	}
	if (flag==1) {
		printf("Max Heap\n");
	} 
	else if (flag==-1) {
		printf("Min Heap\n");
	}
	else {
		printf("Not Heap\n");
	}
}

void solve(int p) {
	if (2*p>n) {  //叶节点 
		vector<int> ve = vector<int>();
		for (int i=p;i>=1;i/=2) {
			ve.push_back(a[i]);
		}
		for (int i=ve.size()-1;i>=0;i--) {
			printf("%d", ve[i]); 
			if (i!=0) {
				printf(" ");
			}
		}
		printf("\n");
	}	
	else {  //2*p<=n
		if (2*p+1<=n) {
			solve(2*p+1);
			solve(2*p);
		}
		else {
			solve(2*p);
		}
	}
}

int main() {
	cin >> n;
	for (int i=1;i<=n;i++) {
		cin >> a[i];
	}
	solve(1);
	judge();
	return 0;
} 
