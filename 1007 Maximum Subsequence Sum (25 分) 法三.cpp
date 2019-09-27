#include <iostream>
#include <algorithm>
using namespace std;

//O(N^2) 暴力法 

int a[10005];

int main() {
	int n;
	cin >> n;
	for (int i=0;i<n;i++) {
		cin >> a[i];
	}
	int tmp = 0;
	int maxsum = -1<<30;
	int begin = 0;
	int end = 0;
	for (int i=0;i<n;i++) {  //O(N^2)的方法 遍历i->j区间 求最大连续和 
		tmp = 0;
		for (int j=i;j<n;j++) {
			tmp += a[j];
			if (tmp > maxsum) {
				maxsum = tmp;
				begin = i;
				end = j;
			}
		}
	}
	if (maxsum < 0) {  //说明全是负数 
		cout << 0 << " " << a[0] << " " << a[n-1];
	}
	else {
		cout << maxsum << " " << a[begin] << " " << a[end]; 
	}
	return 0;	
}
