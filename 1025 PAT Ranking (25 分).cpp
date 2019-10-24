#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
using namespace std;

struct node {
	char id[15];
	int room;
	int score;
	int frank;
	int crank;
	node (char i[], int r, int s) {
		strcpy(id, i);
		room = r;
		score = s;
		frank = 0;
		crank = 0;
	}
	bool operator < (struct node & t) const  {
		if (score > t.score) {
			return 1;
		}
		else if (score < t.score) {
			return 0;
		}
		else {
			int re = strcmp(id, t.id);
			if (re < 0) {
				return 1;
			}
			else if (re > 0) {
				return 0;
			}
		}
	}
};
vector<node> l[105];

int main() {
	int n;
	cin >> n;
	char id[15];
	int score;
	for (int i=1;i<=n;i++) {
		int k;
		cin >> k;
		while (k--) {
			cin >> id >> score;
			l[i].push_back(node(id, i, score));
			l[0].push_back(node(id, i, score));
		}
	}
	cout << l[0].size() << "\n";
	for (int i=0;i<=n;i++) {
		sort(l[i].begin(), l[i].end());
	}
	l[0][0].frank = 1;
	for (int i=1;i<l[0].size();i++) {
		if (l[0][i].score == l[0][i-1].score) {
			l[0][i].frank = l[0][i-1].frank;
		}
		else {
			l[0][i].frank = i+1;
		}
	}
	for (int k=1;k<=n;k++) {
		l[k][0].crank = 1;
		for (int i=1;i<l[k].size();i++) {
			if (l[k][i].score == l[k][i-1].score) {
				l[k][i].crank = l[k][i-1].crank;
			}
			else {
				l[k][i].crank = i+1;
			}
		}
	}
	int cnt[105] = {0};
	for (int i=0;i<l[0].size();i++) {
		cout << l[0][i].id << " " << l[0][i].frank << " " << l[0][i].room << " ";
		for (int j=1;j<=n;j++) {
			if (strcmp(l[j][cnt[j]].id, l[0][i].id)==0) {
				cout << l[j][cnt[j]].crank << "\n";
				cnt[j]++;
				break;
			}
		}
	}
	return 0;
}
