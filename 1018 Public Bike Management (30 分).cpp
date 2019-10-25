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
vector<int> parent[505];  //�����ж������· ����ÿ���ڵ�ĸ��ڵ���ܲ�ֻһ��
int amount[505];  //���е����г���
vector<int> path;
vector<int> tmppath;
int minNeed = 1<<30;
int minBack = 1<<30;

//dijstra�㷨 �ҳ����е����·
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
                    parent[id].clear();  //��id�����·ˢ���� ��ԭ���ĸ��ڵ����
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
    if (v == 0) {  //�����������0 0û�з���path 
        int need = 0, back = 0;
        //�ҵ���һ��·�� ��������·��need��back
        for (int i=tmppath.size()-1;i>=0;i--) {
            if (amount[tmppath[i]] > 0) {
                back += amount[tmppath[i]];  //��Ҫ���ص����
            }
            else {  //ȱ���г� ����ʹ��backȥ�©��
                if (back > -amount[tmppath[i]]) {  //back�㹻
                    back += amount[tmppath[i]];
                }
                else {  //back���� ��Ҫ�������
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
    tmppath.push_back(v);  //���v 
    //dfs v���ڽӵ� �����л� ����Ҫ�б�parent[v][i]�Ƿ�dfs�� 
    for (int i=0;i<parent[v].size();i++) {
        dfs(parent[v][i]);
    }
    tmppath.pop_back();  //���� 
}

int main() {
    cin >> cmax >> n >> sp >> m;
    for (int i=1;i<=n;i++) {
        cin >> amount[i];
        //��ȥcmax/2 ����0˵�����г��� С��0˵�����г���
        amount[i] -= cmax/2;
    }
    int u,v,d;
    while (m--) {
        cin >> u >> v >> d;
        g[u].push_back(node(v, d));
        g[v].push_back(node(u, d));
    }
    dij();  //�����0
    dfs(sp);  //�յ���sp ���յ������0��dfs
    cout << minNeed << " 0";
    for (int i=path.size()-1;i>=0;i--) {
        cout << "->" << path[i];
    }
    cout << " " << minBack << "\n";
    return 0;
}
