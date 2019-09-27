#include <iostream>
#include <algorithm>
using namespace std;

//O(N) 在线处理法
 
int a[10005];

int main() {
	int n;
	cin >> n;
	for (int i=0;i<n;i++) {
		cin >> a[i];
	}
	int thissum = 0;
	int maxsum = -1<<30;
	int st = 0; 
	int ed = 0;
	int ans_st = 0;
	int ans_ed = 0;
	for (int i=0;i<n;i++) {  //O(N)的方法 求最大连续和
		thissum += a[i];
		ed = i;  //更新当前end以i结尾 
		if (thissum > maxsum) {
			maxsum = thissum; 
			ans_st = st;  //更新开始和结尾 
			ans_ed = ed;
		}
		if (thissum < 0) {  //<0则抛弃a[i] 
			thissum = 0;
			st = i+1;  //抛弃a[i] 接下来开头从i+1开始 
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
