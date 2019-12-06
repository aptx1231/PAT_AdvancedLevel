#include<iostream>
#include<algorithm> 
#include<vector>
#include<cstdio>
#include<map>
using namespace std;

struct node {
	int u;
	int v;
	node (int ui,int vi) : u(ui), v(vi) {
	}
};
int color[10005];
vector<node> ve;
map<int, int> colorCnt;

int main() {
	int n,m;
	scanf("%d %d",&n,&m);
	int u,v;
	ve = vector<node>();
	for (int i=0;i<m;i++) {
		scanf("%d %d",&u,&v);
		ve.push_back(node(u, v));
	}
	int k;
	cin >> k;
	while (k--) {
		for (int i=0;i<n;i++) {
			scanf("%d",&color[i]);
			if (colorCnt.find(color[i]) == colorCnt.end()) {
				colorCnt[color[i]] = 0;
			}
		}
		int flag = 0;
		for (int i=0;i<ve.size();i++) {
			if (color[ve[i].u] == color[ve[i].v]) {
				printf("No\n");
				flag = 1;
				break;
			}
		}
		if (!flag) {
			printf("%d-coloring\n",colorCnt.size());
		}
		colorCnt.clear();  //别忘了清空map 重新计数 
	}
	return 0;
} 
