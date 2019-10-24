#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int main() {
	int cnt1[10]={0};
	int cnt2[10]={0};
	char a[25];
	cin >> a;
	int q[25];
	for (int i=0,j=strlen(a)-1;j>=0;i++,j--) {
		q[j] = a[i]-'0';
		cnt1[q[j]]++;
	}
	int b[25]={0};
	for (int i=0;i<=strlen(a)-1;i++) {
		b[i] += q[i]*2;
		b[i+1] += (b[i]/10);
		b[i] %= 10;
	}
	if (b[strlen(a)]) {
		cnt2[b[strlen(a)]]++;
	}
	for (int i=strlen(a)-1;i>=0;i--) {
		cnt2[b[i]]++;
	}
	int f=1;
	for (int i=0;i<10;i++) {
		if (cnt1[i] != cnt2[i]) {
			f = 0;
		}                                                                                
	}
	if (f) {
		cout << "Yes\n";
	}
	else {
		cout << "No\n";
	}
	if (b[strlen(a)]) {  //最高位不为0才输出 
		cout << b[strlen(a)];
	}
	for (int i=strlen(a)-1;i>=0;i--) {
		cout << b[i];
	}
	cout << "\n";
	return 0;
}
