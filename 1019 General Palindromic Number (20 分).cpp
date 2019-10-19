#include <iostream>
#include <algorithm>
using namespace std;

int a[50];

int main() {
	int n,b;
	cin >> n >> b;
	int i=0;
	while (n > 0) {
		a[i] = n % b;
		n /= b;
		i++;
	}	
	int f = 1;
	for (int j=0,k=i-1;j<k;j++,k--) {
		if (a[j] != a[k]) {
			f = 0;
			break;
		}
	}
	if (f) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}
	for (int j=i-1;j>=0;j--) {
		cout << a[j];
		if (j != 0) {
			cout << " ";
		}
	}
	return 0;
}
