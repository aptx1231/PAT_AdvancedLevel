#include <iostream>
#include <algorithm>
using namespace std;

//O(N)动规法
 
int a[10005];

int main() {
	int n;
	cin >> n;
	for (int i=0;i<n;i++) {
		cin >> a[i];
	}
	int maxsum = a[0];
	int thissum = a[0];
	int st = 0; 
	int ed = 0;
	int ans_st = 0;
	int ans_ed = 0;
	for (int i=1;i<n;i++) {  //O(N)的方法 求最大连续和
		if (thissum + a[i] > a[i]) {  //+a[i]可以变大 就变大 a[i]作为end了 
			thissum = thissum + a[i];
			ed = i;
		}
		else {  //这次的最大数列只有a[i]本身 
			thissum = a[i];
			st = i;  //开始和结尾都是i 
			ed = i;
		}
		if (thissum > maxsum) {
			maxsum = thissum;
			ans_st = st;  //更新开始和结尾 
			ans_ed = ed;
		}
	}
	if (maxsum < 0) {  //说明全是负数 
		cout << 0 << " " << a[0] << " " << a[n-1];
	}
	else {
		cout << maxsum << " " << a[ans_st] << " " << a[ans_ed];
	} 
	return 0;	
}
