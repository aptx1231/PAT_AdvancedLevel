#include <iostream>
#include <algorithm>
using namespace std;

long int a[400005];

int main() {
	int n1,n2;
	cin >> n1;
	for (int i=0;i<n1;i++) {
		cin >> a[i];
	}
	cin >> n2;
	for (int i=n1;i<n1+n2;i++) {
		cin >> a[i];
	}
	sort(a,a+n1+n2);
	cout << a[(n1+n2-1)/2];
	return 0;
}
