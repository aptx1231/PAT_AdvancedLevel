#include<iostream>
#include<algorithm> 
#include<map>
#include<vector>
#include<string>
using namespace std;

struct node {
	string id;
	char level;
	int score;
	int data;
	int site;
	node (string i, char l, int s, int d, int si) : 
		id(i), level(l), score(s), data(d), site(si) {
		}
};

map<int, vector<node> > level2ve;
map<int, vector<node> > data2ve;
map<int, vector<node> > site2ve;

int com(struct node& a, struct node& b) {
	if (a.score > b.score) {
		return 1;
	}	
	else if (a.score < b.score) {
		return 0;
	}
	else {
		return a.id < b.id;
	}
}

struct poi2cnt {
	int poi;
	int cnt;
	poi2cnt(int p,int c):poi(p), cnt(c) {
	}
};

int com2(struct poi2cnt& a, struct poi2cnt& b) {
	if (a.cnt > b.cnt) {
		return 1;
	}	
	else if (a.cnt < b.cnt) {
		return 0;
	}
	else {
		return a.poi < b.poi;
	}
}

int main() {
	int n,m;
	cin >> n >> m;
	string a;
	int score;
	for (int i=0;i<n;i++) {
		cin >> a >> score;
		int site = (a[1]-'0')*100+(a[2]-'0')*10+(a[3]-'0');
		int date = (a[4]-'0')*100000+(a[5]-'0')*10000+(a[6]-'0')*1000+ 
				(a[7]-'0')*100+(a[8]-'0')*10+(a[9]-'0');
		int num = (a[10]-'0')*100+(a[11]-'0')*10+(a[12]-'0');
		//cout << a[0] << " " << site << " " << date << " " << num << " " << score << "\n";
		if (level2ve.find(a[0]) == level2ve.end()) {
			level2ve.insert(make_pair(a[0], vector<node>()));
		}
		level2ve[a[0]].push_back(node(a, a[0], score, date, site));
		if (site2ve.find(site) == site2ve.end()) {
			site2ve.insert(make_pair(site, vector<node>()));
		}
		site2ve[site].push_back(node(a, a[0], score, date, site));
		if (data2ve.find(date) == data2ve.end()) {
			data2ve.insert(make_pair(date, vector<node>()));
		}
		data2ve[date].push_back(node(a, a[0], score, date, site));
	}
	for (int i=1;i<=m;i++) {
		int kind;
		string t;
		cin >> kind >> t;
		printf("Case %d: %d %s\n",i,kind,t.c_str());
		if (kind==1) {
			if (level2ve.find(t[0]) != level2ve.end()) {
				vector<node> l = level2ve[t[0]];
				if (l.size() == 0) {
					printf("NA\n");
				}
				else {
					sort(l.begin(), l.end(), com);
					for (int j=0;j<l.size();j++) {
						printf("%s %d\n", l[j].id.c_str(), l[j].score);
					}
				}
			}
			else {
				printf("NA\n");
			}
		}
		else if (kind==2) {
			int site = (t[0]-'0')*100+(t[1]-'0')*10+(t[2]-'0');
			if (site2ve.find(site) != site2ve.end()) {
				vector<node> l = site2ve[site];
				if (l.size() == 0) {
					printf("NA\n");
				}
				else {
					long long total = 0;
					for (int j=0;j<l.size();j++) {
						total += l[j].score;
					}
					printf("%d %lld\n", l.size(), total);
				}
			}
			else {
				printf("NA\n");
			}
		}
		else if (kind==3) {
			int date = (t[0]-'0')*100000+(t[1]-'0')*10000+(t[2]-'0')*1000+ 
				(t[3]-'0')*100+(t[4]-'0')*10+(t[5]-'0');
			if (data2ve.find(date) != data2ve.end()) {
				vector<node> l = data2ve[date];
				if (l.size() == 0) {
					printf("NA\n");
				}
				else {
					int cnt[1000] = {0};
					for (int j=0;j<l.size();j++) {
						cnt[l[j].site]++;
					}
					vector<poi2cnt> l = vector<poi2cnt>();
					for (int i=0;i<=999;i++) {
						if (cnt[i]) {
							l.push_back(poi2cnt(i, cnt[i]));
						}
					}
					sort(l.begin(),l.end(),com2);
					for (int j=0;j<l.size();j++) {
						printf("%d %d\n",l[j].poi, l[j].cnt);
					}
				}
			}
			else {
				printf("NA\n");
			}
		}
		else {
			printf("NA\n");
		}
	}
	return 0;
} 
