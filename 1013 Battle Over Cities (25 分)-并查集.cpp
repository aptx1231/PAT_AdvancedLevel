#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

int a[1005];

struct node {
	int u;
	int v;
	node(int u_,int v_) : u(u_), v(v_) {}
};

void init(int n) {
	for (int i=1;i<=n;i++) {
		a[i] = -1;
	}
}

int find(int r) {
	if (a[r] < 0) {
		return r;
	}
	else {
		return a[r] = find(a[r]);
	}
}

void Union(int r1, int r2) {
	if (a[r1] < a[r2]) {
		a[r1] += a[r2];
		a[r2] = r1;
	}
	else {
		a[r2] += a[r1];
		a[r1] = r2;
	}
}

int main() {
	int n,m,k;
	scanf("%d %d %d",&n,&m,&k);
	vector<node> v;
	int n1,n2;
	for (int i=0;i<m;i++) {
		scanf("%d %d",&n1, &n2);
		v.push_back(node(n1, n2));
	}
	int id;
	while (k--) {
		scanf("%d",&id);
		init(n);
		for (int i=0;i<v.size();i++) {
			int r1 = v[i].u;
			int r2 = v[i].v;
			if (r1 == id || r2 == id) {  //id�Ѿ��������� 
				continue;
			}
			r1 = find(r1);
			r2 = find(r2);
			if (r1 != r2) {
				Union(r1,r2);
			}
		}
		//��¼��ͨ��ĸ��� 
		int tmp = 0;
		for (int i=1;i<=n;i++) {
			if (a[i] < 0) {
				tmp++;
			}
		}
		//��Ҫȥ�������ݵ�id �����ͳ���� idҲ��һ����ͨ���� ������ͨ������tmp-1�� 
		//ͬʱ ������ͨ������Ҫ��һ��·  ����tmp-1����ͨ������Ҫtmp-2��· 
		printf("%d\n",tmp-2);
	}
	return 0;
}
