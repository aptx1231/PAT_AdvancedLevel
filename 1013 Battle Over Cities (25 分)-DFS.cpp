#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

int a[1005][1005];  //�ڽӾ��� 
int vis[1005];
int n,m,k;
int id;

void dfs(int root) {
	vis[root] = 1;
	for (int i=1;i<=n;i++) {
		if (a[root][i]) {
			if (!vis[i]) {
				dfs(i);
			}
		}
	}
}

int main() {
	scanf("%d %d %d",&n,&m,&k);
	int n1,n2;
	for (int i=0;i<m;i++) {
		scanf("%d %d",&n1, &n2);
		a[n1][n2] = 1;
		a[n2][n1] = 1; 
	}
	while (k--) {
		scanf("%d",&id);
		for (int i=1;i<=n;i++) {
			vis[i] = 0;
		}
		int cnt = 0;  //��¼��ͨ�����ĸ��� 
		vis[id] = 1;  //ֻ��Ҫ���id ֮�����Ҳ������ʵ�id�� Ҳ�����id����dfsɨ��
		//������Ҫ�Ѹ�id������a[*][id]��Ϊ0  �޷���ԭ�� 
		for (int i=1;i<=n;i++) {
			if (!vis[i]) {
				dfs(i);
				cnt++;
			}
		}
		//��ʱ��cntû����id�Լ������ͨ���� 
		//������ͨ������Ҫ��һ��·  ����cnt����ͨ������Ҫcnt-1��· 
		printf("%d\n",cnt-1);
	}
	return 0;
}
