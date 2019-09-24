#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

//方式改为二分查找 不再遍历 
 
long long changeTo10(char s[], long long radix) {
	long long ans = 0;
	long long base = 1;
	int len = strlen(s);
	for (int i=len-1;i>=0;i--) {
		if (s[i] >= '0' && s[i] <= '9') {
			ans += (s[i]-'0')*base;
		}
		else {
			ans += (s[i]-'a'+10)*base;
		}
		base *= radix;
	}
	return ans;
}

int main() {
	char n1[15];
	char n2[15];
	int tag,radix;
	cin >> n1 >> n2 >> tag >> radix;
	long long t,w;
	if (tag == 1) {
		t = changeTo10(n1, radix);
	}
	else {
		t = changeTo10(n2, radix);
		strcpy(n2,n1);  //交换一下 之后处理n2即可 跟tag=1一样了 不用重复一遍代码 
	}
	long long l = 0;  //找到最低的进制数 比最大的数位大1 
	for (int i=0;n2[i]!='\0';i++) {
		if (n2[i] >= '0' && n2[i] <= '9') {
			if ((n2[i]-'0') > l) {
				l = n2[i]-'0';
			}
		}
		else {
			if ((n2[i]-'a'+10) > l) {
				l = n2[i]-'a'+10;
			}
		}
	}
	l++;
	long long r = 92e17;  //无限逼近long long最大值了 
	int flag = 0;
	while (l <= r) {
		long long mid = l + (r-l)/2;
		long long w = changeTo10(n2, mid);
		if (w < 0) {  //溢出了 进制太大 
			r = mid-1;
		}
		else if (w == t) {  //找到了 看更小的可以不 r=mid-1 
			flag = 1;
			r = mid-1;
		}
		else if (w > t) {  //进制太大 
			r = mid-1;
		}
		else {  //进制太小 
			l = mid+1;
		}
	}
	if (!flag) {
		cout << "Impossible\n";
	}
	else {
		cout << l;  //输出l 
	}
	return 0;
} 
