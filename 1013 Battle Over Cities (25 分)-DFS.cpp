#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

int a[1005][1005];  //邻接矩阵 
int vis[1005];
int n,m,k;
int id;

void dfs(int root) {
	vis[root] = 1;
	for (int i=1;i<=n;i++) {
		if (a[root][i]) {
			if (!vis[i]) {
				dfs(i);
			}
		}
	}
}

int main() {
	scanf("%d %d %d",&n,&m,&k);
	int n1,n2;
	for (int i=0;i<m;i++) {
		scanf("%d %d",&n1, &n2);
		a[n1][n2] = 1;
		a[n2][n1] = 1; 
	}
	while (k--) {
		scanf("%d",&id);
		for (int i=1;i<=n;i++) {
			vis[i] = 0;
		}
		int cnt = 0;  //记录连通分量的个数 
		vis[id] = 1;  //只需要标记id 之后就再也不会访问到id了 也不会从id进入dfs扫描
		//并不需要把跟id相连的a[*][id]置为0  无法还原了 
		for (int i=1;i<=n;i++) {
			if (!vis[i]) {
				dfs(i);
				cnt++;
			}
		}
		//这时的cnt没有算id自己这个连通分量 
		//两个连通分量需要修一条路  所以cnt个连通分量需要cnt-1条路 
		printf("%d\n",cnt-1);
	}
	return 0;
}
