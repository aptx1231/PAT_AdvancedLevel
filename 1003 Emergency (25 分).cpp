#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

//dijkstra�㷨�ı���
//�����·����ǰ���£�����ж������·��Ҫѡ���ü�ֵ����·
//ͬʱ��Ҫ��¼���·��������
 
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
				if (dist[tmp.id] + we < dist[id]) {  //��չ��һ����tmp.id��id��· 
					dist[id] = dist[tmp.id] + we;
					que.push(node(dist[id], id));
					way[id] = way[tmp.id]; //����id��·�����͵��ڵ���tmp.id��·���� 
					value[id] = value[tmp.id] + amount[id]; //���¼�ֵ ����id�����amount 
				}
				else if (dist[tmp.id] + we == dist[id]) { //��tmp.id��id��·�������ҵ��ĵ���id��·������� 
					//Ҳ�����ҵ���·��һ��������һ��· ��tmp.id���Ե���id 
					way[id] += way[tmp.id]; //��Ҫ�ۻ�����id��·���� �����˵���tmp.id��������ô�� 
					if (value[id] < value[tmp.id] + amount[id]) { //�����tmp.id��id��·�õ��ļ�ֵ�� �͸��� 
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
