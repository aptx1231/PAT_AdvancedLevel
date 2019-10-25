#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

//M/M/N排队论
 
struct node {
	int id;
	int servicetime;
	int arrivetime;
	int startTime;
	int leaveTime;
	int kind;  //到达还是离开 
	int serviceId;
	bool operator< (const node t) const {  //用于优先级队列 
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
	priority_queue<node> que;  //FEL事件列表 
	char arrive[15];
	for (int i=0;i<n;i++) {
		cin >> arrive >> a[i].servicetime;
		a[i].servicetime *= 60;
		a[i].arrivetime = ((arrive[0]-'0')*10+(arrive[1]-'0'))*60*60 + 
					((arrive[3]-'0')*10+(arrive[4]-'0'))*60 +
					(arrive[6]-'0')*10+(arrive[7]-'0');
		a[i].kind = 1;  //到达 
		a[i].startTime = 0;
		a[i].leaveTime = 0;
		a[i].id = i;
		if (a[i].arrivetime <= 17*60*60) {  //只考虑17:00之前到达的 
			que.push(a[i]);
		}  //que中所有顾客都要得到服务 
	}	 
	int status[105] = {0};
	int curTime[105] = {0};
	queue<node> qlist;
	while (!que.empty()) {
		node t = que.top();
		que.pop();
		if (t.kind == 1) {  //到达事件 
			int f = findIdle(status, k);  //查找空闲服务器 
			if (f == -1) {  //没有空闲服务器 则需要进入队列排队 
				qlist.push(t);
			}
			else {  //有空闲服务器 则更新服务器的时间和状态 
				if (t.arrivetime <= 8*60*60) {
					t.arrivetime = 8*60*60;
				}
				//更新服务器的时间和状态 
				curTime[f] = t.arrivetime;
				status[f] = 1;
				//记录a[t.id]的结果 
				a[t.id].startTime = curTime[f];
				a[t.id].serviceId = f;
				//把离开事件加入FEL  注意curTime[f]+t.servicetime 
				que.push(node(t.id, t.servicetime, curTime[f]+t.servicetime, 
					curTime[f], curTime[f]+t.servicetime, 0, f));
			}
		}
		else {  //离开事件 
			int f = t.serviceId;   //离开的顾客本来所在的服务器id 
			//更新服务器的时间
			curTime[f] = t.arrivetime;
			//记录a[t.id]的结果 
			a[t.id].leaveTime = curTime[f];
			if (qlist.empty()) {  //无人排队 服务器f变空闲 
				status[f] = 0;
			}
			else {  //有人排队 队列第一个人进入服务器f执行 
				node t2 = qlist.front();
				qlist.pop();
				//记录a[t2.id]的结果 
				a[t2.id].startTime = curTime[f];
				a[t2.id].serviceId = f;
				//把离开事件加入FEL  注意curTime[f]+t.servicetime 不是t2.starttime 因为没更改t2 
				que.push(node(t2.id, t2.servicetime, curTime[f]+t2.servicetime, 
					curTime[f], curTime[f]+t2.servicetime, 0, f));
			}
		}
	}
	//17点前到达的所有顾客都要得到服务 哪怕他的开始服务时间超过了17点 
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
