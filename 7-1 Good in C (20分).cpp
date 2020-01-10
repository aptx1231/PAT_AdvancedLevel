#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
using namespace std;

string s[30];
char t[100000];

int main() {
	for (int i=0;i<7*26;i++) {
		char t[10];
		cin.getline(t,8);
		s[i/7].append(t);
		//s[i/7].append("\n");
	}
//	for (int i=0;i<26;i++) {
//		cout << s[i];
//		cout << "--------------------------\n";
//	}
	//cin >> t;
	fgets(t, 100000-5, stdin);
	t[strlen(t)]='!';
	t[strlen(t)+1]='\0';
	char out[15];
	int j=0;
	int cnt=0;
	for (int i=0;i<strlen(t);i++) {
		if (t[i]>='A'&&t[i]<='Z') {
			out[j++] = t[i];
		}
		else {
			if (j) {
				cnt++;
			}
			j=0;
		}
	}
	//cout << cnt << endl;
	j=0;
	int tmp=0;
	for (int i=0;i<strlen(t);i++) {
		if (t[i]>='A'&&t[i]<='Z') {
			out[j++] = t[i];
		}
		else {
			if (j) {
				//out[j++] = '\0';
				//cout << out << "\n";
				for (int k=0;k<j;k++) {
					cout << s[out[k]-'A'].substr(0,5);	
					if (k!=j-1) {
						cout << " ";
					}
				}
				cout << "\n";	
				for (int k=0;k<j;k++) {
					cout << s[out[k]-'A'].substr(5,5);	
					if (k!=j-1) {
						cout << " ";
					}
				}
				cout << "\n";
				for (int k=0;k<j;k++) {
					cout << s[out[k]-'A'].substr(10,5);	
					if (k!=j-1) {
						cout << " ";
					}
				}
				cout << "\n";
				for (int k=0;k<j;k++) {
					cout << s[out[k]-'A'].substr(15,5);	
					if (k!=j-1) {
						cout << " ";
					}
				}
				cout << "\n";
				for (int k=0;k<j;k++) {
					cout << s[out[k]-'A'].substr(20,5);	
					if (k!=j-1) {
						cout << " ";
					}
				}
				cout << "\n";
				for (int k=0;k<j;k++) {
					cout << s[out[k]-'A'].substr(25,5);	
					if (k!=j-1) {
						cout << " ";
					}
				}
				cout << "\n";
				for (int k=0;k<j;k++) {
					cout << s[out[k]-'A'].substr(30,5);	
					if (k!=j-1) {
						cout << " ";
					}
				}
				cout << "\n";
				tmp++;
				if (tmp<cnt) {
					cout << "\n";
				}
			}
			j=0;
		}
	}
	return 0;
}