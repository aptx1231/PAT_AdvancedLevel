#include<iostream>
using namespace std;

int isPrim(int num) {
	if (num==1 || num==0) return 0;
	if (num==2) return 1;	
	for (int i=2;i*i<=num;i++) {
		if (num%i==0) {
			return 0;
		}
	}
	return 1;
}

int main() {
	int l,k;
	char a[1005];
	cin >> l >> k;
	cin >> a;
	int flag=0;
	for (int i=0;i+k<=l;i++) {
		int num=0;
		for (int j=i;j<i+k;j++) {
			num *= 10;
			num += (a[j]-'0');
		}
		//cout << num << "\n";
		if (isPrim(num)) {
			flag = 1;
			for (int j=i;j<i+k;j++) {
				printf("%c",a[j]);
			}
			printf("\n");
			break;
		}
	}
	if (flag==0) {
		printf("404\n");
	}
	return 0;
} 
