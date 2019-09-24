#include <iostream>
#include <algorithm>
using namespace std;

int a[10005];

int main() {
	int n;
	cin >> n;
	for (int i=0;i<n;i++) {
		cin >> a[i];
	}
	int tmp = 0;
	int maxsum = -1<<30;
	int end = 0;
	for (int i=0;i<n;i++) {  //O(N)的方法 求最大连续和  但这种方法只能知道序列的结尾是谁 
		tmp += a[i];
		if (tmp > maxsum) {
			maxsum = tmp; 
			end = i;  //更新序列的结尾 
		}
		if (tmp < 0) {
			tmp = 0;
		}
	}
	if (maxsum < 0) {  //说明全是负数 
		cout << 0 << " " << a[0] << " " << a[n-1];
		return 0;
	}
	//已知序列结尾和序列和 找序列开头 O(N) 
	cout << maxsum ;
	int i;
	for (i=end;i>=0;i--) {
		maxsum -= a[i];
		if (maxsum == 0) {
			break;
		}
	}
	//考虑到可能有前缀的0 所以向前找0  注意i-1>=0不能越界！！ 
	while (a[i-1] == 0 && i-1>=0) {
		i--;
	}
	cout << " " << a[i] << " " << a[end];
	return 0;	
}
