#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

int a[10005];
int vis[10005];
vector<int> g[10005];
int ans[10005];

int find(int r) {
	if (a[r] < 0) {
		return r;
	}
	else {
		return a[r] = find(a[r]);
	}
}

void Union(int r1, int r2) {
	if (a[r1] < a[r2]) {
		a[r1] += a[r2];
		a[r2] = r1;		
	}
	else {
		a[r2] += a[r1];
		a[r1] = r2;
	}
}

int maxn;
void dfs(int root, int l) {
	if (l > maxn) {
		maxn = l;
	}
	vis[root] = 1;
	for (int i=0;i<g[root].size();i++) {
		if (vis[g[root][i]] == -1) {
			dfs(g[root][i], l+1);
		}
	}
}

int main() {
	memset(a, -1, sizeof(a));
	int n;
	cin >> n;
	int u,v;
	int f = 1;
	for (int i=0;i<n-1;i++) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
		int r1 = find(u);
		int r2 = find(v);
		if (r1 == r2) {
			f = 0;  //出现了环 
			//Union(r1, r2); 同根不能Union 
		}
		else {
			Union(r1, r2); 
		}
	}
	int k = 0;
	for (int i=1;i<=n;i++) {
		if (a[i] < 0) {
			k++;
		}
	}
	if (f==0 || k!=1) {  //环 或者 不连通 
		printf("Error: %d components\n", k); 
	}
	else {
		int m = -1;
		for (int i=1;i<=n;i++) {
			memset(vis, -1, sizeof(vis));
			maxn = -1;
			dfs(i, 0);
			ans[i] = maxn;
			if (maxn > m) {
				m = maxn;
			}
		}
		for (int i=1;i<=n;i++) {
			if (ans[i] == m) {
				printf("%d\n",i);
			}
		}
 	}
	return 0;
}
