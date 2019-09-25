#include <iostream>
#include <algorithm>
#include <cstdio>
#include <queue> 
using namespace std;

queue<int> que[25];
int n,m;
int tim[1005];
int begins[1005];
int endss[1005];

int main() {
	int k,q;
	scanf("%d %d %d %d",&n,&m,&k,&q);
	for (int i=1;i<=k;i++) {
		scanf("%d",&tim[i]);
	}
	int p = 1;  //�˵ı��
	//0ʱ�� �Ȱ�n*m���˼������ 
	for (int i=0;i<m;i++) {
		for (int j=1;j<=n;j++) {
			que[j].push(p);
			begins[p] = 0;
			p++;
			if (p > k) {
				break;
			}
		} 
	}
	for (int i=1;i<=540;i++) {   //8:00��17:00 9Сʱ ����540���� �ǽ���ʱ��
		//���������ж��Ƿ������������ ��Ҫ���� 
		for (int j=1;j<=n;j++) {
			if (begins[que[j].front()] + tim[que[j].front()] == i) {
				endss[que[j].front()] = i;
				que[j].pop();
				begins[que[j].front()] = i; //�µĶ���ͷ�Ŀ�ʼʱ����i 
			} 
		}
		//���������ж��Ƿ����˿������ 
		while (1) {
			if (p > k) {  //�����˶������ ��Ҫ������ 
				break;
			}
			//ѡ��ǰ��̵Ķ��� 
			int minn = m+1;
			int mini = 0;
			for (int j=1;j<=n;j++) {
				if (que[j].size() < minn) {
					minn = que[j].size();
					mini = j;
				}
			} 
			if (minn < m) {  //��̵Ķ��黹û�� 
				if (p <= k) {
					que[mini].push(p++);  //��p��� 
				}
				else {
					break;
				}
			}
			else {  //��̵Ķ��ж����� ��ǰʱ���޷������ break��ȥ 
				break;
			}
		} 
	}
	//ע����� 17:00֮ǰ���봰�ڽ��ܷ��� ����û�������� ��Ҫ���
	//17:00��֮�� ���봰�ڽ��ܷ��� �Ͳ��ù��� 
	for (int i=1;i<=n;i++) {
		if (que[i].size()) {
			if (begins[que[i].front()] < 540) { //�ж�ÿ������ͷ�Ŀ�ʼʱ�� < 540 ��17:00ǰ���շ���� 
				endss[que[i].front()] = begins[que[i].front()] + tim[que[i].front()];
			}
		}
	}
	int id;
	while (q--) {
		scanf("%d",&id);
		if (endss[id]) {
			int hour = 8;
			int minu = 0;
			hour += (endss[id] / 60);
			minu = endss[id] % 60;
			printf("%02d:%02d\n",hour, minu);
		}
		else {
			printf("Sorry\n");
		}
	}
	return 0;
} 
