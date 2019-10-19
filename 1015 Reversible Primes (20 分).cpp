#include <iostream>
#include <algorithm>
using namespace std;

int isPrime(int n) {
	if (n==1) {
		return 0;
	}
	if (n==2) {
		return 1;
	}
	for (int i=2;i*i<=n;i++) {
		if (n%i==0) {
			return 0;
		}
	}
	return 1;
}

int main() {
	int n,d;
	while (1) {
		cin >> n;
		if (n < 0) {
			break;
		}
		cin >> d;
		if (!isPrime(n)) {
			cout << "No" << endl;
			continue;
		}
		//n化成d进制
		int a[20];
		int i;
		for (i=0;n;i++) {
			a[i] = n%d;
			n /= d;
		} 
		int tmp = 0;
		for (int j=0;j<=i-1;j++) {
			tmp = tmp*d+a[j];
		}
		/*
		int tmp = 0;
		int base = 1;
		for (int j=i-1;j>=0;j--) {
			tmp += a[j]*base;
			base *= d;
		}
		*/
		if (isPrime(tmp)) {
			cout << "Yes" << endl;
		}
		else {
			cout << "No" << endl;
		}
	} 
	return 0;
} 
