#include<iostream>
#include<algorithm>
#include<string>
#include<set>
#include<vector>
using namespace std;

int a[205][205];
int n,m,k;

int main() {
	cin >> n >> m;
	int u,v;
	for (int i=0;i<m;i++) {
		cin >> u >> v;
		a[u][v] = 1;
		a[v][u] = 1;
	}
	cin >> k;
	int l;
	int peo[205];
	for (int i=1;i<=k;i++) {
		cin >> l;
		int color[205] = {0,};
		int select[205] = {0,};
		for (int j=0;j<l;j++) {
			cin >> peo[j];
			color[peo[j]]=1;
		}
		int flag = 1;
		for (int j=0;j<l;j++) {
			for (int kk=j+1;kk<l;kk++) {
				if (a[peo[j]][peo[kk]] == 0) {
					flag = -1;
					break;
				}
			}
			if (flag==-1) {
				break;
			}
		}
		if (flag == -1) {
			printf("Area %d needs help.\n",i);
		}
		else {  
			int need;
			for (int p=1;p<=n;p++) {
				if (color[p]==0) {
					int va=1;
					for (int w=0;w<l;w++) {
						if (a[peo[w]][p]==0) {
							va=0;
							break;
						}
					}
					if (va) {
						need = p;
						flag = 0;
						break;
					}
				}
			}
			if (flag==1) {
				printf("Area %d is OK.\n",i);
			}
			else if (flag==0) {
				printf("Area %d may invite more people, such as %d.\n",i,need);
			}
		}
	}
	return 0;
}
