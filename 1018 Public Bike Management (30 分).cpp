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
int cmax, n, sp, m;
int collect[505];
int dist[505];
vector<int> parent[505];  //可能有多条最短路 所以每个节点的父节点可能不只一个
int amount[505];  //城市的自行车数
vector<int> path;
vector<int> tmppath;
int minNeed = 1<<30;
int minBack = 1<<30;

//dijstra算法 找出所有的最短路
void dij() {
    for (int i=0;i<=n;i++) {
        dist[i] = 1<<30;
        collect[i] = 0;
    }
    priority_queue<node> que;
    dist[0] = 0;
    parent[0].push_back(-1);
    que.push(node(0, 0));
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
                    parent[id].clear();  //到id的最短路刷新了 把原来的父节点清空
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
    if (v == 0) {  //搜索到了起点0 0没有放入path 
        int need = 0, back = 0;
        //找到了一条路径 计算这条路的need和back
        for (int i=tmppath.size()-1;i>=0;i--) {
            if (amount[tmppath[i]] > 0) {
                back += amount[tmppath[i]];  //需要带回到起点
            }
            else {  //缺自行车 优先使用back去填补漏洞
                if (back > -amount[tmppath[i]]) {  //back足够
                    back += amount[tmppath[i]];
                }
                else {  //back不够 需要从起点拿
                    need += (-amount[tmppath[i]] - back);
                    back = 0;
                }
            }
        }
        if (need < minNeed) {
            minNeed = need;
            minBack = back;
            path = tmppath;
        }
        else if (need == minNeed) {
            if (back < minBack) {
                minBack = back;
                path = tmppath;
            }
        }
        return;
    }
    tmppath.push_back(v);  //标记v 
    //dfs v的邻接点 不会有环 不需要判别parent[v][i]是否被dfs过 
    for (int i=0;i<parent[v].size();i++) {
        dfs(parent[v][i]);
    }
    tmppath.pop_back();  //回溯 
}

int main() {
    cin >> cmax >> n >> sp >> m;
    for (int i=1;i<=n;i++) {
        cin >> amount[i];
        //减去cmax/2 大于0说明自行车多 小于0说明自行车少
        amount[i] -= cmax/2;
    }
    int u,v,d;
    while (m--) {
        cin >> u >> v >> d;
        g[u].push_back(node(v, d));
        g[v].push_back(node(u, d));
    }
    dij();  //起点是0
    dfs(sp);  //终点是sp 从终点向起点0做dfs
    cout << minNeed << " 0";
    for (int i=path.size()-1;i>=0;i--) {
        cout << "->" << path[i];
    }
    cout << " " << minBack << "\n";
    return 0;
}
