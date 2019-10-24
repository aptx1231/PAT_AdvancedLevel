#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

struct student {
	string id;
	string name;
	int grade;
}a[100005];

int com1(struct student & a, struct student & b) {
	return a.id < b.id;
}

int com2(struct student & a, struct student & b) {
	if (a.name < b.name) {
		return 1;
	}
	else if (a.name > b.name) {
		return 0;
	}
	else {
		return a.id < b.id;
	}
}

int com3(struct student & a, struct student & b) {
	if (a.grade < b.grade) {
		return 1;
	}
	else if (a.grade > b.grade) {
		return 0;
	}
	else {
		return a.id < b.id;
	}
}

void output(int n) {
	for (int i=0;i<n;i++) {
		cout << a[i].id << " " << a[i].name << " " << a[i].grade << "\n";
	}
}

int main() {
	int n,c;
	cin >> n >> c;
	for (int i=0;i<n;i++) {
		cin >> a[i].id >> a[i].name >> a[i].grade;
	}
	if (c == 1) {
		sort(a, a+n, com1);
		output(n);
	}
	else if (c == 2) {
		sort(a, a+n, com2);
		output(n);
	}
	else if (c == 3) {
		sort(a, a+n, com3);
		output(n);
	}
	return 0;
}
