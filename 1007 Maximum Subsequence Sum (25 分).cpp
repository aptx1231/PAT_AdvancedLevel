#include <iostream>
#include <algorithm>
using namespace std;

//O(N) ���ߴ���
 
int a[10005];

int main() {
	int n;
	cin >> n;
	for (int i=0;i<n;i++) {
		cin >> a[i];
	}
	int thissum = 0;
	int maxsum = -1<<30;
	int st = 0; 
	int ed = 0;
	int ans_st = 0;
	int ans_ed = 0;
	for (int i=0;i<n;i++) {  //O(N)�ķ��� �����������
		thissum += a[i];
		ed = i;  //���µ�ǰend��i��β 
		if (thissum > maxsum) {
			maxsum = thissum; 
			ans_st = st;  //���¿�ʼ�ͽ�β 
			ans_ed = ed;
		}
		if (thissum < 0) {  //<0������a[i] 
			thissum = 0;
			st = i+1;  //����a[i] ��������ͷ��i+1��ʼ 
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
