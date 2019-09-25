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
	int p = 1;  //人的编号
	//0时刻 先把n*m个人加入队列 
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
	for (int i=1;i<=540;i++) {   //8:00到17:00 9小时 遍历540分钟 是结束时间
		//遍历队列判断是否有任务结束了 需要出队 
		for (int j=1;j<=n;j++) {
			if (begins[que[j].front()] + tim[que[j].front()] == i) {
				endss[que[j].front()] = i;
				que[j].pop();
				begins[que[j].front()] = i; //新的队列头的开始时间是i 
			} 
		}
		//遍历队列判断是否有人可以入队 
		while (1) {
			if (p > k) {  //所有人都入队了 不要继续了 
				break;
			}
			//选择当前最短的队列 
			int minn = m+1;
			int mini = 0;
			for (int j=1;j<=n;j++) {
				if (que[j].size() < minn) {
					minn = que[j].size();
					mini = j;
				}
			} 
			if (minn < m) {  //最短的队伍还没满 
				if (p <= k) {
					que[mini].push(p++);  //把p入队 
				}
				else {
					break;
				}
			}
			else {  //最短的队列都满了 当前时间无法入队了 break出去 
				break;
			}
		} 
	}
	//注意的是 17:00之前进入窗口接受服务 但是没完成任务的 需要完成
	//17:00及之后 进入窗口接受服务 就不用管了 
	for (int i=1;i<=n;i++) {
		if (que[i].size()) {
			if (begins[que[i].front()] < 540) { //判断每个队列头的开始时间 < 540 是17:00前接收服务的 
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
