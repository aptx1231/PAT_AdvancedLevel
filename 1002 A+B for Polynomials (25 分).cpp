#include <iostream>
#include <algorithm>
using namespace std;

double a[1005];
double b[1005];
double c[1005];

int main() {
	int la,lb;
	int t;
	double d;
	int maxn = 0;
	cin >> la;
	for (int i=0;i<la;i++) {
		cin >> t >> d;
		a[t] = d;
		if (t > maxn) {
			maxn = t;
		}
	}
	cin >> lb;	
	for (int i=0;i<lb;i++) {
		cin >> t >> d;
		b[t] = d;
		if (t > maxn) {
			maxn = t;
		}
	}
	int cnt=0;
	for (int i=maxn;i>=0;i--) {
		c[i] = a[i]+b[i];
		if (c[i]) {
			cnt++;
		}
	}
	cout << cnt ;
	for (int i=maxn;i>=0;i--) {
		if (c[i]) {
			printf(" %d %0.1lf", i, c[i]);
		}
	}
	return 0;
}
