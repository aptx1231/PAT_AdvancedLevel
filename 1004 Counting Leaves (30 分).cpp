#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

//����� ��ÿһ���м���Ҷ�ڵ�
//����bfs�Ҳ�� ��������ڽӱ��¼
 
struct node {
	int id;
	int level;
	node(int i,int l): id(i), level(l) {}
};

vector<int> g[105];
int vis[105];
int ans[105]; //��¼ÿһ��ĸ��ڵ���Ŀ 
int maxlevel; //��¼һ���ж��ٲ� ������� 

void bfs(int root) {
	queue<node> que;
	vis[root] = 1;
	que.push(node(root, 0));
	maxlevel = 0;
	while (!que.empty()) {
		node tmp = que.front();
		que.pop();
		//��Ϊ���еĵ㶼��������pop����һ�� 
		if (g[tmp.id].size() == 0) { //˵��tmp.idû���ڽӵ� ����һ��Ҷ�ڵ� ����tmp.level�� 
			ans[tmp.level]++; //tmp.level���Ҷ�ڵ����+1 
		}
		for (int i=0;i<g[tmp.id].size();i++) { //�ڽӵ� 
			int id = g[tmp.id][i];
			if (!vis[id]) {
				vis[id] = 1;
				que.push(node(id, tmp.level+1));
				maxlevel = tmp.level+1;
			}
		}		
	}
}

int main() {
	int n,m;
	cin >> n >> m;
	int id;
	int k;
	while(m--) {
		cin >> id >> k;
		int t;
		while (k--) {
			cin >> t;
			g[id].push_back(t);
		}
	}
	bfs(1); //���ڵ���1 
	cout << ans[0];
	for (int i=1;i<=maxlevel;i++) {
		cout << " " << ans[i];
	}
	cout << "\n";
	return 0;
} 
