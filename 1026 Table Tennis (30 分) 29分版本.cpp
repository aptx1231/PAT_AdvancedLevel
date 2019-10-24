#include <iostream>
#include <algorithm>
#include <deque>
#include <queue>
#include <string>
using namespace std;

//最后一个点超时
 
struct node {
	int id;
	int arriveTime;
	int startTime;
	int leaveTime;
	int serveTime;
	int isVip;
	int serveId;
	int kind;
	node (int id_=0, int a=0, int iv=0, int se=0, int k=0, int si=0, int st=0, int le=0) : 
		arriveTime(a), startTime(st), leaveTime(le), serveTime(se), 
			isVip(iv), serveId(si), kind(k), id(id_) {}
	bool operator < (const struct node & t) const {
		return arriveTime > t.arriveTime;
	} 
}a[10005];

int com(struct node & t1, struct node & t2) {
	return t1.arriveTime < t2.arriveTime;
}

int com2(struct node & t1, struct node & t2) {
	return t1.startTime < t2.startTime;
}

int trans(char time[]) {
	int h = (time[0]-'0')*10+(time[1]-'0');
	int m = (time[3]-'0')*10+(time[4]-'0');
	int s = (time[6]-'0')*10+(time[7]-'0');
	return h*60*60+m*60+s;
}

int t[105] = {0};
int status[105] = {0};
int is[105] = {0};
int num[105] = {0};
int m,k;

int find() {
	for (int i=1;i<=k;i++) {
		if (status[i] == 0) {
			return i;
		}
	}	
	return -1;
}	

int findVip() {
	for (int i=1;i<=k;i++) {
		if (status[i] == 0 && is[i] == 1) {
			return i;
		}
	}	
	return -1;
}

void showTime(int time) {
	int h = time/3600;
	time %= 3600;
	int m = time / 60;
	time %= 60;
	int s = time / 1;
	printf("%02d:%02d:%02d ", h, m, s);
}

int main() {
	int n;
	cin >> n;
	priority_queue<node> que;
	char time[20];
	int serve;
	int isVip;
	for (int i=0;i<n;i++) {
		scanf("%s %d %d", time, &serve, &isVip);
		if (serve > 120) {   //最多2小时 即120分钟  超时需要压缩时间 
			serve = 120;
		} 
		a[i] = node(i, trans(time), isVip, serve*60, 0);
		que.push(a[i]);
	}
	cin >> k >> m;
	while (m--) {
		int tmp;
		cin >> tmp;
		is[tmp] = 1; //vip桌 
	}
	deque<node> ve;
	while (!que.empty()) {
		node tmp = que.top();
		que.pop();
		//cout << tmp.arriveTime << endl;
		if (tmp.kind == 0) {  //到达事件 
			if (tmp.isVip) {   //vip用户到达  优先选择vip台 
				int re = findVip();  //找vip空闲服务台
				if (re == -1) {   //没有找到vip空闲服务台 
					re = find();  //找空闲服务台 find不区分是不是vip台 只要是空的就行 
					if (re == -1) {  //没有找到普通空闲服务台 
						ve.push_back(tmp);  //只能排队了 
						sort(ve.begin(), ve.end(), com);
					} 
					else {  //找到普通空闲服务台 
						status[re] = 1;
						t[re] = tmp.arriveTime;
						a[tmp.id].startTime = t[re];
						a[tmp.id].serveId = re;
						que.push(node(tmp.id, t[re]+tmp.serveTime, tmp.isVip, tmp.serveTime, 1, re));
					}
				} 
				else {   //找到vip空闲服务台 
					status[re] = 1;
					t[re] = tmp.arriveTime;
					a[tmp.id].startTime = t[re];
					a[tmp.id].serveId = re;
					que.push(node(tmp.id, t[re]+tmp.serveTime, tmp.isVip, tmp.serveTime, 1, re));
				}
			}
			else {  //普通用户到达 
				int re = find();  //找空闲服务台 find不区分是不是vip台 只要是空的就行 
				if (re == -1) {
					ve.push_back(tmp);
					sort(ve.begin(), ve.end(), com);
				} 
				else {
					status[re] = 1;
					t[re] = tmp.arriveTime;
					a[tmp.id].startTime = t[re];
					a[tmp.id].serveId = re;
					que.push(node(tmp.id, t[re]+tmp.serveTime, tmp.isVip, tmp.serveTime, 1, re));
				}
			}
		}
		else {  //离开事件 
			int re = tmp.serveId;  //离开的服务台编号 
			t[re] = tmp.arriveTime;
			a[tmp.id].leaveTime = t[re];
			if (ve.empty()) {  //无人排队 服务器变空闲
				status[re] = 0;
			}
			else {  //有人排队 
				if (is[re]) {  //离开的是vip服务台 优先找vip用户 
					int i;
					for (i=0;i<ve.size();i++) {
						if (ve[i].isVip) {
							break;
						}
					}
					if (i == ve.size()) {  //没有vip在排队 则取队首 
						node te = ve.front();
						ve.pop_front();
						a[te.id].startTime = t[re];
						a[te.id].serveId = re;
						que.push(node(te.id, t[re]+te.serveTime, te.isVip, te.serveTime, 1, re));
					}
					else {  //有vip排队 vip优先 
						node te = ve[i];
						ve.erase(ve.begin() + i);
						a[te.id].startTime = t[re];
						a[te.id].serveId = re;
						que.push(node(te.id, t[re]+te.serveTime, te.isVip, te.serveTime, 1, re));
					}
				}
				else {  //离开的是普通台 取队首 但是如果队首是vip 需要先去找一个vip台 
					node te = ve.front();
					if (te.isVip) {  //队首是vip 先去找vip台 
						int r = findVip();  //找vip服务台
						if (r == -1) {  //没找到只能用这个普通台了 
							ve.pop_front();
							a[te.id].startTime = t[re];
							a[te.id].serveId = re;
							que.push(node(te.id, t[re]+te.serveTime, te.isVip, te.serveTime, 1, re));
						} 
						else {  //找到了 vip用vip台 普通台标为空 
							status[re] = 0;
							status[r] = 1;
							ve.pop_front();
							t[r] = te.arriveTime;
							a[te.id].startTime = t[r];
							a[te.id].serveId = r;
							que.push(node(te.id, t[r]+te.serveTime, te.isVip, te.serveTime, 1, r));
						}
					} 
					else {  //队首是普通用户 直接用普通台即可 
						ve.pop_front();
						a[te.id].startTime = t[re];
						a[te.id].serveId = re;
						que.push(node(te.id, t[re]+te.serveTime, te.isVip, te.serveTime, 1, re));
					}
				}
			}
		}
	}
	sort(a, a+n, com2);
	for (int i=0;i<n;i++) {
		if (a[i].startTime < 21*60*60) {
			num[a[i].serveId]++;
			showTime(a[i].arriveTime);
			showTime(a[i].startTime);
			if ((a[i].startTime - a[i].arriveTime) % 60 >= 30) {
				printf("%d\n", (a[i].startTime - a[i].arriveTime)/60+1);
			}
			else {
				printf("%d\n", (a[i].startTime - a[i].arriveTime)/60);
			}
		}
	}
	for (int i=1;i<=k;i++) {
		printf("%d", num[i]);
		if (i != k) {
			printf(" ");
		}
	}
	return 0;
} 
