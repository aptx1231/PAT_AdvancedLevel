#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	double a[4];
	int n=3;
	double ans = 1.0;
	while (n--) {
		cin >> a[0] >> a[1] >> a[2];
		if (a[0] > a[1] && a[0] > a[2]) {
			printf("W ");
			ans *= a[0];
		}
		if (a[1] > a[0] && a[1] > a[2]) {
			printf("T ");
			ans *= a[1];
		}
		if (a[2] > a[0] && a[2] > a[1]) {
			printf("L ");
			ans *= a[2];
		}
	}
	ans = (ans*0.65-1.0)*2.0;
	printf("%0.2lf\n",ans);
	return 0;
} 
