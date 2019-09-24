#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

struct node {
	char id[20];
	char begin[15];
	char end[15];
	node (char i[], char b[], char e[]) {
		strcpy(id,i);
		strcpy(begin,b);
		strcpy(end,e);
	}
};

int com1(node & n1, node & n2) {
	if (strcmp(n1.begin, n2.begin) < 0) {
		return 1;
	}
	else {
		return 0;
	}
}

int com2(node & n1, node & n2) {
	if (strcmp(n1.end, n2.end) > 0) {
		return 1;
	}
	else {
		return 0;
	}
}

int main() {
	int m;
	cin >> m;
	char id[20];
	char begin[15];
	char end[15];
	vector<node> v;
	while (m--) {
		scanf("%s %s %s",id,begin,end);
		v.push_back(node(id,begin,end));
	}
	sort(v.begin(), v.end(), com1);
	cout << v[0].id;
	sort(v.begin(), v.end(), com2);
	cout << " " << v[0].id;
	return 0;
} 
