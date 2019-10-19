#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <sstream>
using namespace std;

//错误点 输出id输出7位  printf("%07d\n", v[i]);
//学习 stringstream getline(cin, title); map的使用 

map<string, vector<int> > title2id;
map<string, vector<int> > author2id;
map<string, vector<int> > keyword2id;
map<string, vector<int> > publisher2id;
map<string, vector<int> > year2id;

int main() {
	int n;
	cin >> n;
	int id;
	string title;
	string author;
	string keyword;
	string key;
	string publisher;
	string year;
	while (n--) {
		cin >> id;
		getchar();
		getline(cin, title);
		getline(cin, author);
		getline(cin, keyword);
		getline(cin, publisher);
		getline(cin, year);
		//cout << id << " " << title << " " << author << " " << keyword << " " << publisher << " " << year << endl;
		if (title2id.find(title) != title2id.end()) {
			title2id[title].push_back(id);
		}
		else {
			title2id.insert(make_pair(title, vector<int>()));
			title2id[title].push_back(id);
		}
		if (author2id.find(author) != author2id.end()) {
			author2id[author].push_back(id);
		}
		else {
			author2id.insert(make_pair(author, vector<int>()));
			author2id[author].push_back(id);
		}
		stringstream input(keyword);
		while (input >> key) {
			if (keyword2id.find(key) != keyword2id.end()) {
				keyword2id[key].push_back(id);
			}
			else {
				keyword2id.insert(make_pair(key, vector<int>()));
				keyword2id[key].push_back(id);
			}	
		}
		if (publisher2id.find(publisher) != publisher2id.end()) {
			publisher2id[publisher].push_back(id);
		}
		else {
			publisher2id.insert(make_pair(publisher, vector<int>()));
			publisher2id[publisher].push_back(id);
		}
		if (year2id.find(year) != year2id.end()) {
			year2id[year].push_back(id);
		}
		else {
			year2id.insert(make_pair(year, vector<int>()));
			year2id[year].push_back(id);
		}
	}
	int m;
	cin >> m;
	int k;
	string tmp;
	while (m--) {
		cin >> k;
		getchar();
		getchar();
		getline(cin, tmp);
		cout << k << ": " << tmp << "\n";
		switch (k) {
			case 1:
				if (title2id.find(tmp) != title2id.end()) {
					vector<int> v = title2id[tmp];
					sort(v.begin(), v.end());
					for (int i=0;i<v.size();i++) {
						printf("%07d\n", v[i]);
					}
				}
				else {
					cout << "Not Found\n"; 
				}
				break;
			case 2:
				if (author2id.find(tmp) != author2id.end()) {
					vector<int> v = author2id[tmp];
					sort(v.begin(), v.end());
					for (int i=0;i<v.size();i++) {
						printf("%07d\n", v[i]);
					}
				}
				else {
					cout << "Not Found\n"; 
				}
				break;
			case 3:
				if (keyword2id.find(tmp) != keyword2id.end()) {
					vector<int> v = keyword2id[tmp];
					sort(v.begin(), v.end());
					for (int i=0;i<v.size();i++) {
						printf("%07d\n", v[i]);
					}
				}
				else {
					cout << "Not Found\n"; 
				}
				break;
			case 4:
				if (publisher2id.find(tmp) != publisher2id.end()) {
					vector<int> v = publisher2id[tmp];
					sort(v.begin(), v.end());
					for (int i=0;i<v.size();i++) {
						printf("%07d\n", v[i]);
					}
				}
				else {
					cout << "Not Found\n"; 
				}
				break;
			case 5:
				if (year2id.find(tmp) != year2id.end()) {
					vector<int> v = year2id[tmp];
					sort(v.begin(), v.end());
					for (int i=0;i<v.size();i++) {
						printf("%07d\n", v[i]);
					}
				}
				else {
					cout << "Not Found\n"; 
				}
				break;
		}
	}
	return 0;
}
