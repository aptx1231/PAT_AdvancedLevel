#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

string num[]={"zero","one","two","three","four","five","six","seven","eight","nine"};

int main() {
	char s[105];
	cin >> s;
	int sum = 0;
	for (int i=0;s[i]!='\0';i++) {
		sum += (s[i]-'0');
	}
	int n[105];
	if (sum == 0) {   //±ß½ç 
		cout << num[0];
		return 0;
	}
	int i;
	for (i=0;sum;i++) {
		n[i] = sum%10;
		sum /= 10;
	}
	cout << num[n[i-1]];
	for (int j=i-2;j>=0;j--) {
		cout << " " << num[n[j]];
	}
	return 0;
}
