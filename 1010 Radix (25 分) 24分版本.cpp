#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

//遍历所有可能的进制2->无穷大
//超时了
 
long long changeTo10(char s[], int radix) {
	long long ans = 0;
	long long base = 1;
	int len = strlen(s);
	for (int i=len-1;i>=0;i--) {
		if (s[i] >= '0' && s[i] <= '9') {
			if ((s[i]-'0') >= radix) {
				return -1;
			}
			ans += (s[i]-'0')*base;
		}
		else {
			if ((s[i]-'a'+10) >= radix) {
				return -1;
			}
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
		int ra;
		int flag = 0;
		for (ra=2;;ra++) {
			w = changeTo10(n2, ra);
			if (w == t) {
				flag = 1;
				cout << ra;
				break;
			}
			else if (w > t) {
				break;
			}
		}
		if (!flag) {
			cout << "Impossible\n";
		}
	}
	else {
		t = changeTo10(n2, radix);
		int ra;
		int flag = 0;
		for (ra=2;;ra++) {
			w = changeTo10(n1, ra);
			if (w == t) {
				flag = 1;
				cout << ra;
				break;
			}
			else if (w > t) {
				break;
			}
		}
		if (!flag) {
			cout << "Impossible\n";
		}
	}
	return 0;
} 
