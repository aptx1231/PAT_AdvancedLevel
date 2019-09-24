#include <iostream>
#include <algorithm>
using namespace std;

double a[1005];
double b[1005];
double c[2005];

int main() {
	int la,lb;
	int t;
	double d;
	cin >> la;
	int maxa,maxb;
	for (int i=0;i<la;i++) {
		cin >> t >> d;
		a[t] = d;
		if (i == 0) {
			maxa = t;
		}
	}
	cin >> lb;	
	for (int i=0;i<lb;i++) {
		cin >> t >> d;
		b[t] = d;
		if (i == 0) {
			maxb = t;
		}
	}
	for (int i=maxa;i>=0;i--) {
		for (int j=maxb;j>=0;j--) {
			c[i+j] += a[i] * b[j];
		}
	}
	int cnt=0;
	for (int i=maxa+maxb;i>=0;i--) {
		if (c[i]) {
			cnt++;
		}
	}
	cout << cnt ;
	for (int i=maxa+maxb;i>=0;i--) {
		if (c[i]) {
			printf(" %d %0.1lf", i, c[i]);
		}
	}
	return 0;
}
