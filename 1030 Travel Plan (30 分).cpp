#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct node {
	int id;
	int dist;
	int cost;
	node (int i,int d,int c) : id(i), dist(d), cost(c) {}
};

vector<node> g[505];
int n,m,s,t;
int collect[505];
int dist[505];
int parent[505];
int cost[505];

int findMin() {
	int mind = 1<<30;
	int minv = -1;
	for (int i=0;i<n;i++) {
		if (collect[i]==0) {
			if (dist[i] < mind) {
				mind = dist[i];
				minv = i;
			}
		}
	}	
	if (mind != 1<<30) {
		return minv;
	}
	else {
		return -1;
	}
}

void dij() {
	for (int i=0;i<n;i++) {
		dist[i] = 1<<30;
		cost[i] = 1<<30;
		collect[i] = 0;
		parent[i] = -1;
	}
	dist[s] = 0;
	parent[s] = -1;
	cost[s] = 0;
	while (1) {
		int t = findMin();
		if (t == -1) {
			break;
		}
		collect[t] = 1;
		for (int i=0;i<g[t].size();i++) {
			int id = g[t][i].id;
			int di = g[t][i].dist;
			int co = g[t][i].cost;
			if (!collect[id]) {
				if (dist[id] > dist[t] + di) {
					dist[id] = dist[t] + di;
					parent[id] = t;
					cost[id] = cost[t] + co;
				}
				else if (dist[id] == dist[t] + di) {
					if (cost[id] > cost[t] + co) {
						cost[id] = cost[t] + co;
						parent[id] = t;
					}
				}
			}
		}
	}
}

int main() {
	cin >> n >> m >> s >> t;
	int u,v,d,c;
	while (m--) {
		cin >> u >> v >> d >> c;
		g[u].push_back(node(v, d, c));
		g[v].push_back(node(u, d, c));
	}
	dij();
	int path[505]={0};
	int i=0;
	int tmp = t;
	while (parent[tmp] != -1) {
		path[i++] = parent[tmp];
		tmp = parent[tmp];
	}
	for (int j=i-1;j>=0;j--) {
		cout << path[j] << " ";
	}
	cout << t;
	cout << " " << dist[t];
	cout << " " << cost[t];
	return 0;
}
