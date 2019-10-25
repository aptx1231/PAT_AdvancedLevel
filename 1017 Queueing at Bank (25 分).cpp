#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

//M/M/N�Ŷ���
 
struct node {
	int id;
	int servicetime;
	int arrivetime;
	int startTime;
	int leaveTime;
	int kind;  //���ﻹ���뿪 
	int serviceId;
	bool operator< (const node t) const {  //�������ȼ����� 
		return arrivetime > t.arrivetime;
	}
	node (int id=0, int se=0, int ar=0, int st=0, int le=0, int kind=1, int sid=-1) :
		id(id), servicetime(se), arrivetime(ar), startTime(st),
		leaveTime(le), kind(kind), serviceId(sid)  {}
}a[10005];

int findIdle(int status[], int k) {
	for (int i=0;i<k;i++) {
		if (status[i] == 0) {
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
	cout << h << ":" << m << ":" << s << endl;
}

int main() {
	int n,k;
	cin >> n >> k;
	priority_queue<node> que;  //FEL�¼��б� 
	char arrive[15];
	for (int i=0;i<n;i++) {
		cin >> arrive >> a[i].servicetime;
		a[i].servicetime *= 60;
		a[i].arrivetime = ((arrive[0]-'0')*10+(arrive[1]-'0'))*60*60 + 
					((arrive[3]-'0')*10+(arrive[4]-'0'))*60 +
					(arrive[6]-'0')*10+(arrive[7]-'0');
		a[i].kind = 1;  //���� 
		a[i].startTime = 0;
		a[i].leaveTime = 0;
		a[i].id = i;
		if (a[i].arrivetime <= 17*60*60) {  //ֻ����17:00֮ǰ����� 
			que.push(a[i]);
		}  //que�����й˿Ͷ�Ҫ�õ����� 
	}	 
	int status[105] = {0};
	int curTime[105] = {0};
	queue<node> qlist;
	while (!que.empty()) {
		node t = que.top();
		que.pop();
		if (t.kind == 1) {  //�����¼� 
			int f = findIdle(status, k);  //���ҿ��з����� 
			if (f == -1) {  //û�п��з����� ����Ҫ��������Ŷ� 
				qlist.push(t);
			}
			else {  //�п��з����� ����·�������ʱ���״̬ 
				if (t.arrivetime <= 8*60*60) {
					t.arrivetime = 8*60*60;
				}
				//���·�������ʱ���״̬ 
				curTime[f] = t.arrivetime;
				status[f] = 1;
				//��¼a[t.id]�Ľ�� 
				a[t.id].startTime = curTime[f];
				a[t.id].serviceId = f;
				//���뿪�¼�����FEL  ע��curTime[f]+t.servicetime 
				que.push(node(t.id, t.servicetime, curTime[f]+t.servicetime, 
					curTime[f], curTime[f]+t.servicetime, 0, f));
			}
		}
		else {  //�뿪�¼� 
			int f = t.serviceId;   //�뿪�Ĺ˿ͱ������ڵķ�����id 
			//���·�������ʱ��
			curTime[f] = t.arrivetime;
			//��¼a[t.id]�Ľ�� 
			a[t.id].leaveTime = curTime[f];
			if (qlist.empty()) {  //�����Ŷ� ������f����� 
				status[f] = 0;
			}
			else {  //�����Ŷ� ���е�һ���˽��������fִ�� 
				node t2 = qlist.front();
				qlist.pop();
				//��¼a[t2.id]�Ľ�� 
				a[t2.id].startTime = curTime[f];
				a[t2.id].serviceId = f;
				//���뿪�¼�����FEL  ע��curTime[f]+t.servicetime ����t2.starttime ��Ϊû����t2 
				que.push(node(t2.id, t2.servicetime, curTime[f]+t2.servicetime, 
					curTime[f], curTime[f]+t2.servicetime, 0, f));
			}
		}
	}
	//17��ǰ��������й˿Ͷ�Ҫ�õ����� �������Ŀ�ʼ����ʱ�䳬����17�� 
	long long total = 0;
	int cnt = 0;
	for (int i=0;i<n;i++) {
		if (a[i].arrivetime <= 17*60*60) {
			total += (a[i].startTime - a[i].arrivetime);
			cnt++;
		}
	}
	printf("%.1lf\n", total/60.0/cnt);
	return 0;
}
