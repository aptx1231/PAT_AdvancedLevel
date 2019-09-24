#include <iostream>
#include <algorithm>
using namespace std;

int a[10005];

int main() {
	int n;
	cin >> n;
	for (int i=0;i<n;i++) {
		cin >> a[i];
	}
	int tmp = 0;
	int maxsum = -1<<30;
	int end = 0;
	for (int i=0;i<n;i++) {  //O(N)�ķ��� �����������  �����ַ���ֻ��֪�����еĽ�β��˭ 
		tmp += a[i];
		if (tmp > maxsum) {
			maxsum = tmp; 
			end = i;  //�������еĽ�β 
		}
		if (tmp < 0) {
			tmp = 0;
		}
	}
	if (maxsum < 0) {  //˵��ȫ�Ǹ��� 
		cout << 0 << " " << a[0] << " " << a[n-1];
		return 0;
	}
	//��֪���н�β�����к� �����п�ͷ O(N) 
	cout << maxsum ;
	int i;
	for (i=end;i>=0;i--) {
		maxsum -= a[i];
		if (maxsum == 0) {
			break;
		}
	}
	//���ǵ�������ǰ׺��0 ������ǰ��0  ע��i-1>=0����Խ�磡�� 
	while (a[i-1] == 0 && i-1>=0) {
		i--;
	}
	cout << " " << a[i] << " " << a[end];
	return 0;	
}
