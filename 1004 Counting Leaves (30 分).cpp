#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

//多叉树 求每一层有几个叶节点
//采用bfs找层次 多叉树用邻接表记录
 
struct node {
	int id;
	int level;
	node(int i,int l): id(i), level(l) {}
};

vector<int> g[105];
int vis[105];
int ans[105]; //记录每一层的根节点数目 
int maxlevel; //记录一共有多少层 用于输出 

void bfs(int root) {
	queue<node> que;
	vis[root] = 1;
	que.push(node(root, 0));
	maxlevel = 0;
	while (!que.empty()) {
		node tmp = que.front();
		que.pop();
		//因为所有的点都会在这里pop出来一次 
		if (g[tmp.id].size() == 0) { //说明tmp.id没有邻接点 他是一个叶节点 他在tmp.level层 
			ans[tmp.level]++; //tmp.level层的叶节点个数+1 
		}
		for (int i=0;i<g[tmp.id].size();i++) { //邻接点 
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
	bfs(1); //根节点是1 
	cout << ans[0];
	for (int i=1;i<=maxlevel;i++) {
		cout << " " << ans[i];
	}
	cout << "\n";
	return 0;
} 
