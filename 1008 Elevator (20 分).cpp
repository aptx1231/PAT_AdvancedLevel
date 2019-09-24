#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int n;
	cin >> n;
	int a[105];
	for (int i=0;i<n;i++) {
		cin >> a[i];
	}
	int tmp = 0;
	int ans = 0;
	for (int i=0;i<n;i++) {
		if (a[i] > tmp) {
			ans += (a[i]-tmp) * 6;
		}
		else if (a[i] < tmp) {
			ans += (tmp-a[i]) * 4;
		}
		tmp = a[i];
		ans += 5;
	}
	cout << ans << endl;
	return 0;
} 
