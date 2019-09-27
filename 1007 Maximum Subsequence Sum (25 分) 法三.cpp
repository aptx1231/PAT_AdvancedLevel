#include <iostream>
#include <algorithm>
using namespace std;

//O(N^2) ������ 

int a[10005];

int main() {
	int n;
	cin >> n;
	for (int i=0;i<n;i++) {
		cin >> a[i];
	}
	int tmp = 0;
	int maxsum = -1<<30;
	int begin = 0;
	int end = 0;
	for (int i=0;i<n;i++) {  //O(N^2)�ķ��� ����i->j���� ����������� 
		tmp = 0;
		for (int j=i;j<n;j++) {
			tmp += a[j];
			if (tmp > maxsum) {
				maxsum = tmp;
				begin = i;
				end = j;
			}
		}
	}
	if (maxsum < 0) {  //˵��ȫ�Ǹ��� 
		cout << 0 << " " << a[0] << " " << a[n-1];
	}
	else {
		cout << maxsum << " " << a[begin] << " " << a[end]; 
	}
	return 0;	
}
