#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int a,b,c;
	cin >> a >> b >> c;
	printf("#");
	if (a/13 >= 10) {
		printf("%c", a/13 - 10 + 'A');
	}
	else {
		printf("%d", a/13);
	}
	if (a%13 >= 10) {
		printf("%c", a%13 - 10 + 'A');
	}
	else {
		printf("%d", a%13);
	}
	a = b;
	if (a/13 >= 10) {
		printf("%c", a/13 - 10 + 'A');
	}
	else {
		printf("%d", a/13);
	}
	if (a%13 >= 10) {
		printf("%c", a%13 - 10 + 'A');
	}
	else {
		printf("%d", a%13);
	}
	a = c;
	if (a/13 >= 10) {
		printf("%c", a/13 - 10 + 'A');
	}
	else {
		printf("%d", a/13);
	}
	if (a%13 >= 10) {
		printf("%c", a%13 - 10 + 'A');
	}
	else {
		printf("%d", a%13);
	}
	return 0;
}
