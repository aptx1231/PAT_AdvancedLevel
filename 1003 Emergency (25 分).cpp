#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

//dijkstra算法的变形
//在最短路径的前提下，如果有多条最短路，要选择获得价值最大的路
//同时需要记录最短路径的条数
 
struct node {
	int weight;
	int id;
	node(int weight, int id) : weight(weight), id(id) {}
	bool operator< (const node & t) const {
		return weight > t.weight;
	}
};

int n,m,c1,c2;
vector<node> g[505];
int amount[505];
int dist[505];
int way[505];
int value[505];
int visit[505];

void dij(int e) {
	for (int i=0;i<n;i++) {
		dist[i] = 1<<30;
		visit[i] = 0;
		way[i] = 0;
		value[i] = 0;
	}
	priority_queue<node> que;
	dist[e] = 0;
	way[e] = 1;
	value[e] = amount[e];
	que.push(node(0, e));
	while (!que.empty()) {
		node tmp = que.top();
		que.pop();
		if (visit[tmp.id]) {
			continue;
		}
		visit[tmp.id] = 1;
		for (int i=0;i<g[tmp.id].size();i++) {
			int id = g[tmp.id][i].id;
			int we = g[tmp.id][i].weight;
			if (!visit[id]) {
				if (dist[tmp.id] + we < dist[id]) {  //发展了一条从tmp.id到id的路 
					dist[id] = dist[tmp.id] + we;
					que.push(node(dist[id], id));
					way[id] = way[tmp.id]; //到达id的路径数就等于到达tmp.id的路径数 
					value[id] = value[tmp.id] + amount[id]; //更新价值 加上id本身的amount 
				}
				else if (dist[tmp.id] + we == dist[id]) { //从tmp.id到id的路跟本来找到的到达id的路长度相等 
					//也就是找到了路程一样长的另一条路 从tmp.id可以到达id 
					way[id] += way[tmp.id]; //需要累积到达id的路径数 增加了到达tmp.id的数量那么多 
					if (value[id] < value[tmp.id] + amount[id]) { //如果走tmp.id到id的路得到的价值大 就更新 
						value[id] = value[tmp.id] + amount[id];
					}
				}
			}
		}
	}	
}

int main() {
	cin >> n >> m >> c1 >> c2;
	for (int i=0;i<n;i++) {
		cin >> amount[i];
	}
	int u,v,l;
	for (int i=0;i<m;i++) {
		cin >> u >> v >> l;
		g[u].push_back(node(l, v));
		g[v].push_back(node(l, u));
	}
	dij(c1);
	cout << way[c2] << " " << value[c2];
	return 0;
}
