#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

//��ʽ��Ϊ���ֲ��� ���ٱ��� 
 
long long changeTo10(char s[], long long radix) {
	long long ans = 0;
	long long base = 1;
	int len = strlen(s);
	for (int i=len-1;i>=0;i--) {
		if (s[i] >= '0' && s[i] <= '9') {
			ans += (s[i]-'0')*base;
		}
		else {
			ans += (s[i]-'a'+10)*base;
		}
		base *= radix;
	}
	return ans;
}

int main() {
	char n1[15];
	char n2[15];
	int tag,radix;
	cin >> n1 >> n2 >> tag >> radix;
	long long t,w;
	if (tag == 1) {
		t = changeTo10(n1, radix);
	}
	else {
		t = changeTo10(n2, radix);
		strcpy(n2,n1);  //����һ�� ֮����n2���� ��tag=1һ���� �����ظ�һ����� 
	}
	long long l = 0;  //�ҵ���͵Ľ����� ��������λ��1 
	for (int i=0;n2[i]!='\0';i++) {
		if (n2[i] >= '0' && n2[i] <= '9') {
			if ((n2[i]-'0') > l) {
				l = n2[i]-'0';
			}
		}
		else {
			if ((n2[i]-'a'+10) > l) {
				l = n2[i]-'a'+10;
			}
		}
	}
	l++;
	long long r = 92e17;  //���ޱƽ�long long���ֵ�� 
	int flag = 0;
	while (l <= r) {
		long long mid = l + (r-l)/2;
		long long w = changeTo10(n2, mid);
		if (w < 0) {  //����� ����̫�� 
			r = mid-1;
		}
		else if (w == t) {  //�ҵ��� ����С�Ŀ��Բ� r=mid-1 
			flag = 1;
			r = mid-1;
		}
		else if (w > t) {  //����̫�� 
			r = mid-1;
		}
		else {  //����̫С 
			l = mid+1;
		}
	}
	if (!flag) {
		cout << "Impossible\n";
	}
	else {
		cout << l;  //���l 
	}
	return 0;
} 
