#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

struct node {
    int id;
    int dist;
    node (int i,int d) : id(i), dist(d) {}
    bool operator < (const node & t) const {
        return dist > t.dist;
    }
};

vector<node> g[505];
int n,m,s,t;
int collect[505];
int dist[505];
int cost[505][505];  //记录任意两点间的花费
vector<int> parent[505];  //可能有多条最短路 所以每个节点的父节点可能不只一个
vector<int> path;
vector<int> tmppath;
int minCost = 1<<30;

//dijstra算法 找出所有的最短路
void dij() {
    for (int i=0;i<n;i++) {
        dist[i] = 1<<30;
        collect[i] = 0;
    }
    priority_queue<node> que;
    dist[s] = 0;
    parent[s].push_back(-1);
    que.push(node(s, 0));
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
            if (!collect[id]) {
                if (dist[id] > dist[t.id] + di) {
                    dist[id] = dist[t.id] + di;
                    que.push(node(id, dist[id]));
                    parent[id].clear();
                    parent[id].push_back(t.id);
                }
                else if (dist[id] == dist[t.id] + di) {
                    parent[id].push_back(t.id);
                }
            }
        }
    }
}

void dfs(int v) {
    if (v == s) {
    	//s没有放到tmppath里边 但是cost需要加s到tmppath最后一个点的距离 
        int tmp = cost[s][tmppath[tmppath.size()-1]];
        for (int i=tmppath.size()-1;i>=1;i--) {
            tmp += cost[tmppath[i]][tmppath[i-1]];
        }
        if (tmp < minCost) {
            minCost = tmp;
            path = tmppath;
        }
        return;
    }
    tmppath.push_back(v);
    for (int i=0;i<parent[v].size();i++) {
        dfs(parent[v][i]);
    }
    tmppath.pop_back();
}

int main() {
    cin >> n >> m >> s >> t;
    int u,v,d,c;
    while (m--) {
        cin >> u >> v >> d >> c;
        g[u].push_back(node(v, d));
        g[v].push_back(node(u, d));
        cost[u][v] = cost[v][u] = c;
    }
    dij();  //找出所有最短路 
    dfs(t); //遍历所有路径 找cost最小的 
    cout << s;
    for (int i=path.size()-1;i>=0;i--) {
        cout << " " << path[i];
    }
    cout << " " << dist[t];
    cout << " " << minCost << "\n";
    return 0;
}
