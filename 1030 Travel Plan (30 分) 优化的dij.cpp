#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

struct node {
	int id;
	int dist;
	int cost;
	node (int i,int d,int c) : id(i), dist(d), cost(c) {}
	bool operator < (const node & t) const {
		return dist > t.dist;
	}
};

vector<node> g[505];
int n,m,s,t;
int collect[505];
int dist[505];
int parent[505];
int cost[505];

void dij() {
	for (int i=0;i<n;i++) {
		dist[i] = 1<<30;
		cost[i] = 1<<30;
		collect[i] = 0;
		parent[i] = -1;
	}
	priority_queue<node> que;
	dist[s] = 0;
	parent[s] = -1;
	cost[s] = 0;
	que.push(node(s, 0, 0));
	while (!que.empty()) {
		node t = que.top();
		que.pop();
		if (collect[t.id]) {
			continue;
		}
		collect[t.id] = 1; 
		for (int i=0;i<g[t.id].size();i++) {
			int id = g[t.id][i].id;
			int di = g[t.id][i].dist;
			int co = g[t.id][i].cost;
			if (!collect[id]) {
				if (dist[id] > dist[t.id] + di) {
					dist[id] = dist[t.id] + di;
					parent[id] = t.id;
					cost[id] = cost[t.id] + co;
					que.push(node(id, dist[id], cost[id]));
				}
				else if (dist[id] == dist[t.id] + di) {
					if (cost[id] > cost[t.id] + co) {
						cost[id] = cost[t.id] + co;
						parent[id] = t.id;
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
