#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

char a[100];
char b[100];
int k;

int isPalindromic(char s[]) {
	for (int i=0,j=strlen(s)-1;i<=j;i++,j--) {
		if (a[i] != a[j]) {
			return 0;
		}
	}	
	return 1;
}

void add(char a[], char b[]) {
	int c[100]={0};
	int n = strlen(a);
	for (int i=0;i<n;i++) {
		c[i] += (a[i]-'0' + b[i]-'0');
		c[i+1] += c[i]/10;
		c[i] %= 10;
	}
	int j=0;
	if (c[n] != 0) {
		a[j++] = c[n]+'0';
	}
	for (int i=n-1;i>=0;i--) {
		a[j++] = c[i]+'0';
	}
	a[j] = '\0';
	//cout << a << "\n";
}

int main() {
	cin >> a >> k;		
	if (isPalindromic(a)) {
		cout << a << "\n" << 0 << "\n";
		return 0;
	}
	int l;
	for (l=1;l<=k;l++) {
		for (int i=0,j=strlen(a)-1;j>=0;i++,j--) {
			b[i] = a[j];
		}
		//cout << a << " " << b << "\n";
		add(a, b);
		if (isPalindromic(a)) {
			cout << a << "\n" << l << "\n";
			break;
		}
	}
	if (l == k+1) {
		cout << a << "\n" << k << "\n";
	}
	return 0;
}
