#include <iostream>
#include <algorithm>
#include <deque>
#include <queue>
#include <string>
using namespace std;

//���һ���㳬ʱ
 
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
		if (serve > 120) {   //���2Сʱ ��120����  ��ʱ��Ҫѹ��ʱ�� 
			serve = 120;
		} 
		a[i] = node(i, trans(time), isVip, serve*60, 0);
		que.push(a[i]);
	}
	cin >> k >> m;
	while (m--) {
		int tmp;
		cin >> tmp;
		is[tmp] = 1; //vip�� 
	}
	deque<node> ve;
	while (!que.empty()) {
		node tmp = que.top();
		que.pop();
		//cout << tmp.arriveTime << endl;
		if (tmp.kind == 0) {  //�����¼� 
			if (tmp.isVip) {   //vip�û�����  ����ѡ��vip̨ 
				int re = findVip();  //��vip���з���̨
				if (re == -1) {   //û���ҵ�vip���з���̨ 
					re = find();  //�ҿ��з���̨ find�������ǲ���vip̨ ֻҪ�ǿյľ��� 
					if (re == -1) {  //û���ҵ���ͨ���з���̨ 
						ve.push_back(tmp);  //ֻ���Ŷ��� 
						sort(ve.begin(), ve.end(), com);
					} 
					else {  //�ҵ���ͨ���з���̨ 
						status[re] = 1;
						t[re] = tmp.arriveTime;
						a[tmp.id].startTime = t[re];
						a[tmp.id].serveId = re;
						que.push(node(tmp.id, t[re]+tmp.serveTime, tmp.isVip, tmp.serveTime, 1, re));
					}
				} 
				else {   //�ҵ�vip���з���̨ 
					status[re] = 1;
					t[re] = tmp.arriveTime;
					a[tmp.id].startTime = t[re];
					a[tmp.id].serveId = re;
					que.push(node(tmp.id, t[re]+tmp.serveTime, tmp.isVip, tmp.serveTime, 1, re));
				}
			}
			else {  //��ͨ�û����� 
				int re = find();  //�ҿ��з���̨ find�������ǲ���vip̨ ֻҪ�ǿյľ��� 
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
		else {  //�뿪�¼� 
			int re = tmp.serveId;  //�뿪�ķ���̨��� 
			t[re] = tmp.arriveTime;
			a[tmp.id].leaveTime = t[re];
			if (ve.empty()) {  //�����Ŷ� �����������
				status[re] = 0;
			}
			else {  //�����Ŷ� 
				if (is[re]) {  //�뿪����vip����̨ ������vip�û� 
					int i;
					for (i=0;i<ve.size();i++) {
						if (ve[i].isVip) {
							break;
						}
					}
					if (i == ve.size()) {  //û��vip���Ŷ� ��ȡ���� 
						node te = ve.front();
						ve.pop_front();
						a[te.id].startTime = t[re];
						a[te.id].serveId = re;
						que.push(node(te.id, t[re]+te.serveTime, te.isVip, te.serveTime, 1, re));
					}
					else {  //��vip�Ŷ� vip���� 
						node te = ve[i];
						ve.erase(ve.begin() + i);
						a[te.id].startTime = t[re];
						a[te.id].serveId = re;
						que.push(node(te.id, t[re]+te.serveTime, te.isVip, te.serveTime, 1, re));
					}
				}
				else {  //�뿪������̨ͨ ȡ���� �������������vip ��Ҫ��ȥ��һ��vip̨ 
					node te = ve.front();
					if (te.isVip) {  //������vip ��ȥ��vip̨ 
						int r = findVip();  //��vip����̨
						if (r == -1) {  //û�ҵ�ֻ���������̨ͨ�� 
							ve.pop_front();
							a[te.id].startTime = t[re];
							a[te.id].serveId = re;
							que.push(node(te.id, t[re]+te.serveTime, te.isVip, te.serveTime, 1, re));
						} 
						else {  //�ҵ��� vip��vip̨ ��̨ͨ��Ϊ�� 
							status[re] = 0;
							status[r] = 1;
							ve.pop_front();
							t[r] = te.arriveTime;
							a[te.id].startTime = t[r];
							a[te.id].serveId = r;
							que.push(node(te.id, t[r]+te.serveTime, te.isVip, te.serveTime, 1, r));
						}
					} 
					else {  //��������ͨ�û� ֱ������̨ͨ���� 
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
