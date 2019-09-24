#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int a,b;
	cin >> a >> b;
	int c[10];
	int ans = a+b;
	if (ans == 0) {  //边界！！！ 
		printf("0\n");
		return 0;
	} 
	if (ans < 0) {
		cout << "-";
		ans = -ans;
	}
	int i;
	for (i=1;ans;i++) {  //数字转换成数组 
		c[i] = ans % 10;
		ans /= 10;
	}
	i--; //[1-i]都是有效值 
	int leave = i % 3;
	if (leave==0) {
		leave=3;
	}
	//输出不能整除3的部分 
	for (int j=0;j<leave;j++) {
		printf("%d",c[i--]);
	}
	//三个三个的输出 
	for (;i>=1;i-=3) {
		printf(",%d%d%d",c[i],c[i-1],c[i-2]);
	}
	return 0;
}
