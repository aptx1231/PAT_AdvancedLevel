#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int a,b;
	cin >> a >> b;
	int c[10];
	int ans = a+b;
	if (ans == 0) {  //�߽磡���� 
		printf("0\n");
		return 0;
	} 
	if (ans < 0) {
		cout << "-";
		ans = -ans;
	}
	int i;
	for (i=1;ans;i++) {  //����ת�������� 
		c[i] = ans % 10;
		ans /= 10;
	}
	i--; //[1-i]������Чֵ 
	int leave = i % 3;
	if (leave==0) {
		leave=3;
	}
	//�����������3�Ĳ��� 
	for (int j=0;j<leave;j++) {
		printf("%d",c[i--]);
	}
	//������������� 
	for (;i>=1;i-=3) {
		printf(",%d%d%d",c[i],c[i-1],c[i-2]);
	}
	return 0;
}
