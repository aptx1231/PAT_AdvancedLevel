#include <iostream>
#include <algorithm>
using namespace std;

//O(N)���淨
 
int a[10005];

int main() {
	int n;
	cin >> n;
	for (int i=0;i<n;i++) {
		cin >> a[i];
	}
	int maxsum = a[0];
	int thissum = a[0];
	int st = 0; 
	int ed = 0;
	int ans_st = 0;
	int ans_ed = 0;
	for (int i=1;i<n;i++) {  //O(N)�ķ��� �����������
		if (thissum + a[i] > a[i]) {  //+a[i]���Ա�� �ͱ�� a[i]��Ϊend�� 
			thissum = thissum + a[i];
			ed = i;
		}
		else {  //��ε��������ֻ��a[i]���� 
			thissum = a[i];
			st = i;  //��ʼ�ͽ�β����i 
			ed = i;
		}
		if (thissum > maxsum) {
			maxsum = thissum;
			ans_st = st;  //���¿�ʼ�ͽ�β 
			ans_ed = ed;
		}
	}
	if (maxsum < 0) {  //˵��ȫ�Ǹ��� 
		cout << 0 << " " << a[0] << " " << a[n-1];
	}
	else {
		cout << maxsum << " " << a[ans_st] << " " << a[ans_ed];
	} 
	return 0;	
}
