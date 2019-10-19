#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <string>
using namespace std;

int cost[30];
struct node{
	char name[25];
	char time[15];
	int kind;
	bool operator< (const node t) const {
		int ans = strcmp(name, t.name);
		if (ans < 0) {
			return 1;
		}
		else if (ans > 0) {
			return 0;
		}
		else {
			ans = strcmp(time, t.time);
			if (ans < 0) {
				return 1;
			}
			else if (ans > 0) {
				return 0;
			}
		}
	}
}a[1005];

ostream& operator<< (ostream& o, const node& t) {
	o << t.name << " " << t.time << " " << t.kind << "\n";
}

void cal(int start, int end, int & minu, double & money) {
	int sd = (a[start].time[3]-'0')*10+(a[start].time[4]-'0');
	int sh = (a[start].time[6]-'0')*10+(a[start].time[7]-'0');
	int sm = (a[start].time[9]-'0')*10+(a[start].time[10]-'0');
	int ed = (a[end].time[3]-'0')*10+(a[end].time[4]-'0');
	int eh = (a[end].time[6]-'0')*10+(a[end].time[7]-'0');
	int em = (a[end].time[9]-'0')*10+(a[end].time[10]-'0');
	//cout << sd << " " << sh << " " << sm << " " << ed << " " << eh << " " << em << endl;
	minu = (ed*24*60+eh*60+em) - (sd*24*60+sh*60+sm);
	//cout << minu << "\n";
	money = 0;
	int t = minu;
	if (t >= (60-sm)) {
		money += (cost[sh] * (60 - sm));
		t -= (60-sm);
		while (t >= 60) {
			sh++;
			if (sh >= 24) {
				sh = 0;
			}
			money += cost[sh] * 60;
			t -= 60;
		}
		sh++;
		if (sh >= 24) {
			sh = 0;
		}
		money += cost[sh] * t;
	}
	else {
		money += cost[sh] * t;
	}
	money /= 100;
	//cout << money << "\n";
}

int main() {
	for (int i=0;i<24;i++) {
		cin >> cost[i];
	}
	int n;
	cin >> n;
	char s[10];
	for (int i=0;i<n;i++) {
		cin >> a[i].name >> a[i].time >> s;
		if (s[1] == 'n') {
			a[i].kind = 1;
		}
		else {
			a[i].kind = 0;
		}
	}
	sort(a, a+n);
	//for (int i=0;i<n;i++) {
	//	cout << a[i];
	//}
	set<string> set;
	double total = 0;
	for (int i=0;i+1<n;i++) {
		if (strcmp(a[i].name, a[i+1].name) == 0) {
			if (a[i].kind == 1 && a[i+1].kind == 0) {
				if (set.find(string(a[i].name)) == set.end()) {
					set.insert(string(a[i].name));
					cout << a[i].name << " " << a[i].time[0] << a[i].time[1] << "\n";
				} 
				cout << a[i].time+3 << " " << a[i+1].time+3;
				int minu = 0;
				double money = 0;
				cal(i, i+1, minu, money);
				total += money;
				cout << " " << minu << " $";
				printf("%.2lf\n", money);
			}
		}
		else {
			if (set.find(string(a[i].name)) != set.end()) {
				cout << "Total amount: $";
				printf("%.2lf\n", total);
				total = 0;
			} 
		}
	}
	if (set.find(string(a[n-1].name)) != set.end()) {
		cout << "Total amount: $";
		printf("%.2lf\n", total);
	} 
	return 0;
} 
